package it.unibo.seiot.smartdumpster.model;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.FormatStyle;
import java.util.Collections;

import com.google.common.net.HttpHeaders;

import io.vertx.core.Vertx;
import io.vertx.core.http.HttpClient;
import io.vertx.core.http.HttpClientResponse;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.RoutingContext;

/**
 * 
 */
public class ServiceHttpClient {
    private static final String HOST = "192.168.1.38";
    private static final String LOGS_PATH = System.getProperty("user.home")
                                            + System.getProperty("file.separator")
                                            + "logs"
                                            + System.getProperty("file.separator");
    private static final String LOG_EXTENSION = ".log";
    private static final String DEPOSIT_ROUTE = "/deposit";
    private static final String STATE_ROUTE = "/state";
    private static final String JSON_MIME_TYPE = "application/json";
    private static final String COUNT_JSON_KEY = "count";
    private static final String WEIGHT_JSON_KEY = "weight";
    private static final String AVAILABLE_JSON_KEY = "available";
    private static final String DEPOSIT_JSON_KEY = "deposit";
    private static final String BEGIN_DEPOSIT_JSON_VALUE = "begin";
    private static final String END_DEPOSIT_JSON_VALUE = "end";

    private final HttpClient client;
    private final Vertx vertx;

    /**
     * 
     * @param vertx the Vertx instance launched.
     */
    public ServiceHttpClient(final Vertx vertx) {
        this.vertx = vertx;
        this.client = this.vertx.createHttpClient();
    }
    /**
     * 
     * @param routingContext the object holding information about the request made for this begin deposit action
     */
    public void getCurrentState(final RoutingContext routingContext) {
        final HttpServerResponse response = routingContext.response();
        this.client.get(HOST, STATE_ROUTE, edgeResponse -> {
            if (!edgeResponse.succeeded()) {
                response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                return;
            }
            edgeResponse.result().body(edgeResponseBody -> {
                if (!edgeResponseBody.succeeded()) {
                    response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                    return;
                }
                final JsonObject jsonEdgeResponseBody = edgeResponseBody.result().toJsonObject();
                if (jsonEdgeResponseBody == null
                    || !JsonParserUtils.hasJsonCorrectField(jsonEdgeResponseBody,
                                                            AVAILABLE_JSON_KEY,
                                                            Boolean.class,
                                                            Collections.emptySet())
                    || !JsonParserUtils.hasJsonCorrectField(jsonEdgeResponseBody,
                                                            WEIGHT_JSON_KEY,
                                                            Integer.class,
                                                            Collections.emptySet())) {
                    response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                    return;
                }
                final JsonObject jsonResponse = new JsonObject().put(AVAILABLE_JSON_KEY,
                                                                     jsonEdgeResponseBody.getBoolean(AVAILABLE_JSON_KEY))
                                                                .put(WEIGHT_JSON_KEY,
                                                                     jsonEdgeResponseBody.getInteger(WEIGHT_JSON_KEY));
                this.vertx.executeBlocking(promise -> {
                    final String fileName = LOGS_PATH
                                            + LocalDate.now()
                                                       .format(DateTimeFormatter.ofLocalizedDate(FormatStyle.SHORT))
                                                       .replace("/", "")
                                            + LOG_EXTENSION;
                    try (RandomAccessFile file = new RandomAccessFile(fileName, "rw")) {
                        if (file.length() == 0) {
                            file.writeInt(0);
                            file.writeInt(0);
                            file.seek(0);
                        }
                        jsonResponse.put(COUNT_JSON_KEY, file.readInt());
                        response.putHeader(HttpHeaders.CONTENT_TYPE, JSON_MIME_TYPE).end(jsonResponse.encode());
                        promise.complete();
                    } catch (final IOException ex) {
                        response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                        promise.fail(ex);
                    }
                });
            });
        }).end();
    }
    /**
     * 
     * @param available if the state of the smart dumpster controller has to be set to "available" or to "not available".
     * @param routingContext the object holding information about the request made for this begin deposit action.
     */
    public void setAvailableState(final boolean available, final RoutingContext routingContext) {
        final JsonObject jsonRequestBody = new JsonObject();
        jsonRequestBody.put(AVAILABLE_JSON_KEY, available);
        this.client.put(HOST, STATE_ROUTE)
                   .putHeader(HttpHeaders.CONTENT_TYPE, JSON_MIME_TYPE)
                   .setHandler(edgeResponse -> {
                       routingContext.response().setStatusCode(edgeResponse.succeeded()
                                                               ? edgeResponse.result().statusCode()
                                                               : HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                   })
                   .end(jsonRequestBody.encode());
    }
    /**
     * 
     * @param routingContext the object holding information about the request made for this begin deposit action.
     */
    public void beginDeposit(final RoutingContext routingContext) {
        final JsonObject jsonRequestBody = new JsonObject();
        jsonRequestBody.put(DEPOSIT_JSON_KEY, BEGIN_DEPOSIT_JSON_VALUE);
        this.client.put(HOST, DEPOSIT_ROUTE)
                   .putHeader(HttpHeaders.CONTENT_TYPE, JSON_MIME_TYPE)
                   .setHandler(edgeResponse -> {
                       routingContext.response().setStatusCode(edgeResponse.succeeded()
                                                               ? edgeResponse.result().statusCode()
                                                               : HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                   })
                   .end(jsonRequestBody.encode());
    }
    /**
     * 
     * @param routingContext the object holding information about the request made for this begin deposit action.
     */
    public void endDeposit(final RoutingContext routingContext) {
        final JsonObject jsonRequestBody = new JsonObject();
        jsonRequestBody.put(DEPOSIT_JSON_KEY, END_DEPOSIT_JSON_VALUE);
        this.client.put(HOST, DEPOSIT_ROUTE)
                   .putHeader(HttpHeaders.CONTENT_TYPE, JSON_MIME_TYPE)
                   .setHandler(edgeResponse -> {
                       final HttpClientResponse result = edgeResponse.result();
                       final HttpServerResponse response = routingContext.response();
                       if (!edgeResponse.succeeded()) {
                           response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                           return;
                       } else if (result.statusCode() != HttpStatus.OK.getCode()) {
                           response.setStatusCode(result.statusCode()).end();
                           return;
                       }
                       result.body(responseBody -> {
                           if (!responseBody.succeeded()
                               || !JsonParserUtils.hasJsonCorrectField(responseBody.result().toJsonObject(),
                                                                       WEIGHT_JSON_KEY,
                                                                       Integer.class,
                                                                       Collections.emptySet())) {
                               response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                               return;
                           }
                           final int weight = responseBody.result().toJsonObject().getInteger(WEIGHT_JSON_KEY);
                           this.vertx.executeBlocking(promise -> {
                               final String fileName = LOGS_PATH
                                                       + LocalDate.now()
                                                                  .format(DateTimeFormatter.ofLocalizedDate(FormatStyle.SHORT))
                                                                  .replace("/", "")
                                                       + LOG_EXTENSION;
                               try (RandomAccessFile file = new RandomAccessFile(fileName, "rw")) {
                                   if (file.length() == 0) {
                                       file.writeInt(1);
                                       file.writeInt(weight);
                                   } else {
                                       final int count = file.readInt();
                                       final int currentWeight = file.readInt();
                                       file.seek(0);
                                       file.writeInt(count + 1);
                                       file.writeInt(currentWeight + weight);
                                   }
                                   response.setStatusCode(HttpStatus.OK.getCode()).end();
                                   promise.complete();
                               } catch (final IOException ex) {
                                   response.setStatusCode(HttpStatus.INTERNAL_SERVER_ERROR.getCode()).end();
                                   promise.fail(ex);
                               }
                           });
                       });
                   })
                   .end(jsonRequestBody.encode());
    }
}
