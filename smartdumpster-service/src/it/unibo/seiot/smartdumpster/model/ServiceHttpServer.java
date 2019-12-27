package it.unibo.seiot.smartdumpster.model;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.charset.Charset;
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
 * 
 */
public class ServiceHttpServer extends AbstractVerticle {
    private static final int PORT = 8080;
    private static final int N_DAYS = 5;
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

    private Optional<ServiceHttpClient> client;
    private Optional<String> token;
    private boolean lastDepositEarlyEnded;

    /**
     * 
     */
    public ServiceHttpServer() {
        super();
        this.client = Optional.empty();
        this.token = Optional.empty();
        this.lastDepositEarlyEnded = false;
    }
    /**
     * @throws Exception 
     */
    @Override
    public void start() throws Exception {
        super.start();
        this.client = Optional.of(new ServiceHttpClient(this.vertx));
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
     * 
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
     * 
     */
    private void getEdgeLog(final RoutingContext routingContext) {
        this.vertx.executeBlocking(promise -> {
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
            routingContext.response().putHeader(HttpHeaders.CONTENT_TYPE, JSON_MIME_TYPE).end(log.encode());
            promise.complete();
        });
    }
    /*
     * 
     */
    private void getToken(final RoutingContext routingContext) {
        final HttpServerResponse response = routingContext.response();
        if (this.token.isPresent()) {
            response.setStatusCode(HttpStatus.FORBIDDEN.getCode()).end();
            return;
        }
        this.token = Optional.of(Hashing.sha256()
                                        .hashString(Instant.now().toString() + new Random().nextInt(),
                                                    Charset.defaultCharset())
                                        .toString());
        response.putHeader(HttpHeaders.CONTENT_TYPE, JSON_MIME_TYPE)
                .end(new JsonObject().put(TOKEN_JSON_KEY, this.token.get()).encode());
    }
    /**
     * 
     */
    private void changeDepositState(final RoutingContext routingContext) {
        final HttpServerResponse response = routingContext.response();
        final JsonObject jsonRequest = routingContext.getBodyAsJson();
        if (jsonRequest == null
            || !JsonParserUtils.hasJsonCorrectField(jsonRequest, 
                                                    DEPOSIT_JSON_KEY,
                                                    String.class,
                                                    new HashSet<>(Arrays.asList(BEGIN_DEPOSIT_JSON_VALUE,
                                                                                END_DEPOSIT_JSON_VALUE)))
            || !JsonParserUtils.hasJsonCorrectField(jsonRequest,
                                                    TOKEN_JSON_KEY,
                                                    String.class,
                                                    Collections.emptySet())) {
            response.setStatusCode(HttpStatus.BAD_REQUEST.getCode()).end();
            return;
        }
        if (this.token.isEmpty() || !jsonRequest.getString(TOKEN_JSON_KEY).equals(this.token.get())) {
            response.setStatusCode(HttpStatus.FORBIDDEN.getCode()).end();
            return;
        }
        final String operation = jsonRequest.getString(DEPOSIT_JSON_KEY);
        if (operation.equals(BEGIN_DEPOSIT_JSON_VALUE)) {
            this.client.orElseThrow(IllegalStateException::new).beginDeposit(routingContext);
        } else if (!this.lastDepositEarlyEnded) {
            this.client.orElseThrow(IllegalStateException::new).endDeposit(routingContext);
            this.token = Optional.empty();
        } else {
            this.lastDepositEarlyEnded = false;
            response.setStatusCode(HttpStatus.OK.getCode()).end();
        }
    }
    /*
     * 
     */
    private void earlyEndDeposit(final RoutingContext routingContext) {
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
        this.lastDepositEarlyEnded = true;
        this.token = Optional.empty();
        this.vertx.executeBlocking(promise -> {
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
