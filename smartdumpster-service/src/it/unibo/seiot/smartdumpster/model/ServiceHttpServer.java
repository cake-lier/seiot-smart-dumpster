/* Authors: Matteo Castellucci, Giorgia Rondinini */
package it.unibo.seiot.smartdumpster.model;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.Instant;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.FormatStyle;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.Optional;
import java.util.Random;
import java.util.stream.IntStream;

import com.google.common.hash.Hashing;
import com.google.common.net.HttpHeaders;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.StaticHandler;

/**
 * A class representing the web server component of the Service. It manages http connections
 * from the Android App, the Dashboard (a web browser) and the Edge, on different routes.
 */
public class ServiceHttpServer extends AbstractVerticle {
    private static final int PORT = 8080;
    private static final int N_DAYS = 5;
    private static final long TOKEN_DURATION_MS = 1000 * 60 * 5;
    private static final long DEPOSIT_DURATION_MS = 1000 * (90 * 2 + 20);
    private static final String LOGS_PATH = System.getProperty("user.home")
                                            + System.getProperty("file.separator")
                                            + "logs"
                                            + System.getProperty("file.separator");
    private static final String LOG_EXTENSION = ".log";
    private static final String ROOT = "/";
    private static final String DASHBOARD_ROUTE = "/dashboard";
    private static final String DASHBOARD_ROOT = DASHBOARD_ROUTE + ROOT;
    private static final String DASHBOARD_ALL_SUBROUTES = DASHBOARD_ROOT + "*";
    private static final String TOKEN_ROUTE = "/token";
    private static final String DEPOSIT_ROUTE = "/deposit";
    private static final String EARLY_END_ROUTE = DEPOSIT_ROUTE + "/early_end";
    private static final String STATE_ROUTE = DASHBOARD_ROUTE + "/state";
    private static final String CURRENT_DATA_ROUTE = DASHBOARD_ROUTE + "/current_data";
    private static final String LOG_ROUTE = DASHBOARD_ROUTE + "/log";
    private static final String JSON_MIME_TYPE = "application/json";
    private static final String WEIGHT_JSON_KEY = "weight";
    private static final String AVAILABLE_JSON_KEY = "available";
    private static final String DEPOSIT_JSON_KEY = "deposit";
    private static final String TOKEN_JSON_KEY = "token";
    private static final String BEGIN_DEPOSIT_JSON_VALUE = "begin";
    private static final String END_DEPOSIT_JSON_VALUE = "end";
    private static final String KEEP_ALIVE_JSON_VALUE = "continue";
    private static final String ERROR_CREATE_LOG_DIR = "Could not create log directory";

    private final DumpsterEdge edge;
    private Optional<ServiceHttpClient> client;
    private Optional<String> token;
    private volatile long tokenTimerID;
    private volatile long depositTimerID;

    /**
     * Builds a new {@link ServiceHttpServer}.
     */
    public ServiceHttpServer() {
        super();
        this.client = Optional.empty();
        this.token = Optional.empty();
        this.edge = new DumpsterEdgeImpl();
        this.tokenTimerID = 0;
        this.depositTimerID = 0;
    }
    /**
     * {@inheritDoc}
     */
    @Override
    public void start() throws Exception {
        super.start();
        this.client = Optional.of(new ServiceHttpClient(this.vertx, this.edge));
        final Router router = Router.router(this.vertx);
        router.route().handler(BodyHandler.create());
        router.route(DASHBOARD_ALL_SUBROUTES).handler(StaticHandler.create());
        router.route(DASHBOARD_ROUTE).handler(routingContext -> routingContext.redirect(DASHBOARD_ROOT));
        router.route(ROOT).handler(routingContext -> routingContext.redirect(DASHBOARD_ROOT));
        router.put(EARLY_END_ROUTE).consumes(JSON_MIME_TYPE).handler(this::earlyEndDeposit);
        router.get(TOKEN_ROUTE).handler(this::getToken);
        router.put(DEPOSIT_ROUTE).consumes(JSON_MIME_TYPE).handler(this::changeDepositState);
        router.put(STATE_ROUTE).consumes(JSON_MIME_TYPE).handler(this::changeEdgeState);
        router.get(CURRENT_DATA_ROUTE).handler(this.client.orElseThrow(IllegalStateException::new)::getCurrentState);
        router.get(LOG_ROUTE).handler(this::getEdgeLog);
        this.vertx.createHttpServer().requestHandler(router).listen(PORT);
    }
    /*
     * Manager for messages received on the {@link #STATE_ROUTE} route, it is used for keeping the state of the representation of
     * the Edge kept inside of the Service in line with the physical version.
     */
    private void changeEdgeState(final RoutingContext routingContext) {
        final JsonObject jsonRequestBody = routingContext.getBodyAsJson();
        if (jsonRequestBody == null
            || !JsonParserUtils.hasJsonCorrectField(jsonRequestBody,
                                                    AVAILABLE_JSON_KEY,
                                                    Boolean.class,
                                                    Collections.emptySet())) {
            routingContext.response().setStatusCode(HttpStatus.BAD_REQUEST.getCode()).end();
            return;
        }
        this.client.orElseThrow(IllegalStateException::new)
                   .setAvailableState(jsonRequestBody.getBoolean(AVAILABLE_JSON_KEY), routingContext);
    }
    /*
     * Manager for messages received on the {@link #LOG_ROUTE}, it sends the log data (mantained on file) as an answer to the
     * request.
     */
    private void getEdgeLog(final RoutingContext routingContext) {
        this.vertx.executeBlocking(promise -> {
            final HttpServerResponse response = routingContext.response();
            final Path logPath = Paths.get(LOGS_PATH);
            if (Files.exists(logPath) && !Files.isDirectory(logPath)) {
                response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                promise.fail(ERROR_CREATE_LOG_DIR);
                return;
            }
            try {
                Files.createDirectories(Paths.get(LOGS_PATH));
            } catch (final IOException ex) {
                response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                promise.fail(ex);
                return;
            }
            final LocalDate date = LocalDate.now();
            final JsonArray log = new JsonArray();
            IntStream.range(0, N_DAYS)
                     .forEach(i -> {
                         final String dateString = date.minusDays(N_DAYS - 1 - i)
                                                       .format(DateTimeFormatter.ofLocalizedDate(FormatStyle.SHORT));
                         final String fileName = LOGS_PATH + dateString.replace("/", "") + LOG_EXTENSION;
                         try (RandomAccessFile file = new RandomAccessFile(fileName, "rw")) {
                             final JsonArray logLine = new JsonArray().add(dateString);
                             if (file.length() == 0) {
                                 file.writeInt(0);
                                 file.writeInt(0);
                                 logLine.add(0).add(0);
                             } else {
                                 logLine.add(file.readInt()).add(file.readInt());
                             }
                             log.add(logLine);
                         } catch (IOException ex) {
                             promise.fail(ex);
                         }
                     });
            response.putHeader(HttpHeaders.CONTENT_TYPE, JSON_MIME_TYPE).end(log.encode());
            promise.complete();
        });
    }
    /*
     * Manager for messages received on the {@link #TOKEN_ROUTE} route, it send a new token as an answer to the request
     * received, it that request was correctly formatted and there is no other active token in use.
     */
    private void getToken(final RoutingContext routingContext) {
        final HttpServerResponse response = routingContext.response();
        if (this.token.isPresent() || !this.edge.isStateAvailable()) {
            response.setStatusCode(HttpStatus.FORBIDDEN.getCode()).end();
            return;
        }
        this.token = Optional.of(Hashing.sha256()
                                        .hashString(Instant.now().toString() + new Random().nextInt(),
                                                    Charset.defaultCharset())
                                        .toString());
        response.putHeader(HttpHeaders.CONTENT_TYPE, JSON_MIME_TYPE)
                .end(new JsonObject().put(TOKEN_JSON_KEY, this.token.get()).encode());
        this.tokenTimerID = this.vertx.setTimer(TOKEN_DURATION_MS, id -> {
            synchronized (this) {
                if (!this.edge.hasDepositBegun()) {
                    this.token = Optional.empty();
                }
            }
        });
    }
    /*
     * Creates a new timer to check if a deposit has been going on for too long.
     */
    private void createDepositTimer() {
        this.depositTimerID = this.vertx.setTimer(DEPOSIT_DURATION_MS, id -> {
            synchronized (this) {
                if (this.depositTimerID == id && this.edge.hasDepositBegun()) {
                    this.token = Optional.empty();
                    this.edge.endDeposit();
                    if (!this.edge.hasLastDepositEarlyEnded()) {
                        this.client.orElseThrow(IllegalStateException::new).endDeposit();
                    }
                }
            }
        });
    }
    /*
     * Manager for messages received on the {@link #DEPOSIT_ROUTE} route, it checks if the message received is correctly
     * formatted and authorized (using a correct token) and if so communicates to the Edge the status of the current deposit.
     */
    private void changeDepositState(final RoutingContext routingContext) {
        final HttpServerResponse response = routingContext.response();
        final JsonObject jsonRequest = routingContext.getBodyAsJson();
        if (jsonRequest == null
            || !JsonParserUtils.hasJsonCorrectField(jsonRequest, 
                                                    DEPOSIT_JSON_KEY,
                                                    String.class,
                                                    new HashSet<>(Arrays.asList(BEGIN_DEPOSIT_JSON_VALUE,
                                                                                END_DEPOSIT_JSON_VALUE,
                                                                                KEEP_ALIVE_JSON_VALUE)))
            || !JsonParserUtils.hasJsonCorrectField(jsonRequest,
                                                    TOKEN_JSON_KEY,
                                                    String.class,
                                                    Collections.emptySet())) {
            response.setStatusCode(HttpStatus.BAD_REQUEST.getCode()).end();
            return;
        }
        synchronized (this) {
            if (this.token.isEmpty() || !jsonRequest.getString(TOKEN_JSON_KEY).equals(this.token.get())) {
                response.setStatusCode(HttpStatus.FORBIDDEN.getCode()).end();
                return;
            }
            final String operation = jsonRequest.getString(DEPOSIT_JSON_KEY);
            if (operation.equals(BEGIN_DEPOSIT_JSON_VALUE)) {
                if (this.edge.hasDepositBegun()) {
                    response.setStatusCode(HttpStatus.FORBIDDEN.getCode()).end();
                    return;
                }
                this.vertx.cancelTimer(this.tokenTimerID);
                this.createDepositTimer();
                this.edge.beginDeposit();
                this.edge.setEarlyEnd(false);
                this.client.orElseThrow(IllegalStateException::new).beginDeposit(routingContext);
            } else if (operation.equals(END_DEPOSIT_JSON_VALUE)) {
                if (!this.edge.hasDepositBegun() || !this.edge.isStateAvailable()) {
                    response.setStatusCode(HttpStatus.FORBIDDEN.getCode()).end();
                    return;
                }
                this.token = Optional.empty();
                this.edge.endDeposit();
                this.vertx.cancelTimer(this.depositTimerID);
                if (!this.edge.hasLastDepositEarlyEnded()) {
                    this.client.orElseThrow(IllegalStateException::new).endDeposit(routingContext);
                } else {
                    response.setStatusCode(HttpStatus.OK.getCode()).end();
                }
            } else if (operation.equals(KEEP_ALIVE_JSON_VALUE)) {
                if (!this.edge.hasDepositBegun()) {
                    response.setStatusCode(HttpStatus.FORBIDDEN.getCode()).end();
                    return;
                }
                this.vertx.cancelTimer(this.depositTimerID);
                this.createDepositTimer();
                response.setStatusCode(HttpStatus.OK.getCode()).end();
            }
        }
    }
    /*
     * Manager for messages on the {@link #EARLY_END_ROUTE} route, coming from the Edge.
     */
    private synchronized void earlyEndDeposit(final RoutingContext routingContext) {
        final HttpServerResponse response = routingContext.response();
        final JsonObject jsonRequestBody = routingContext.getBodyAsJson();
        if (jsonRequestBody == null
            || !JsonParserUtils.hasJsonCorrectField(jsonRequestBody,
                                                    WEIGHT_JSON_KEY,
                                                    Integer.class,
                                                    Collections.emptySet())) {
            response.setStatusCode(HttpStatus.BAD_REQUEST.getCode()).end();
            return;
        }
        this.edge.setEarlyEnd(true);
        this.vertx.executeBlocking(promise -> {
            final Path logPath = Paths.get(LOGS_PATH);
            if (Files.exists(logPath) && !Files.isDirectory(logPath)) {
                response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                promise.fail(ERROR_CREATE_LOG_DIR);
                return;
            }
            try {
                Files.createDirectories(Paths.get(LOGS_PATH));
            } catch (final IOException ex) {
                response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                promise.fail(ex);
                return;
            }
            final String fileName = LOGS_PATH
                                    + LocalDate.now()
                                               .format(DateTimeFormatter.ofLocalizedDate(FormatStyle.SHORT))
                                               .replace("/", "")
                                    + LOG_EXTENSION;
            try (RandomAccessFile file = new RandomAccessFile(fileName, "rw")) {
                if (file.length() == 0) {
                    file.writeInt(1);
                    file.writeInt(jsonRequestBody.getInteger(WEIGHT_JSON_KEY));
                } else {
                    final int count = file.readInt();
                    final int currentWeight = file.readInt();
                    file.seek(0);
                    file.writeInt(count + 1);
                    file.writeInt(currentWeight + jsonRequestBody.getInteger(WEIGHT_JSON_KEY));
                }
                response.setStatusCode(HttpStatus.OK.getCode()).end();
                promise.complete();
            } catch (final IOException ex) {
                response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                promise.fail(ex);
            }
        });
    }
}
