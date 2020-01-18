package it.unibo.seiot.gm.smartdumpsterapp.app;

import android.util.Log;
import android.util.Pair;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.ProtocolException;
import java.util.Optional;
import java.util.function.BiFunction;

/**
 * An enum representing the possible ways a message using HTTP can be send.
 */
public enum HTTPConnectionMethod {
    /**
     * An HTTP GET request.
     */
    GET((c, p) -> {
        try {
            c.setRequestMethod("GET");
            if (c.getResponseCode() == HttpURLConnection.HTTP_OK) {
                return Pair.create(c.getResponseCode(), Optional.of(c.getInputStream()));
            } else {
                Log.d("HTTPConnectionMethod", "Request result: " + c.getResponseCode());
                return Pair.create(c.getResponseCode(), Optional.empty());
            }
        } catch (ProtocolException e) {
            Log.e("SmartDumpsterApp_HTTPMethods", "Problemi con il protocollo HTTP");
            return Pair.create(0, Optional.empty());
        } catch (IOException e) {
            Log.e("SmartDumpsterApp_HTTPMethods", "Problemi con il risultato della comunicazione HTTP");
            return Pair.create(0, Optional.empty());
        }
    }),
    /**
     * An HTTP POST request.
     */
    POST((c,p) -> {
        try {
            c.setRequestMethod("POST");
            c.setDoOutput(true);
            if (p.isPresent()) {
                c.getOutputStream().write(p.get());
            }
            if (c.getResponseCode() == HttpURLConnection.HTTP_OK) {
                return Pair.create(c.getResponseCode(), Optional.of(c.getInputStream()));
            } else {
                Log.d("HTTPConnectionMethod", "Request result: " + c.getResponseCode());
                return Pair.create(c.getResponseCode(), Optional.empty());
            }
        } catch (ProtocolException e) {
            Log.e("SmartDumpsterApp_HTTPMethods", "Problemi con il protocollo HTTP");
            return Pair.create(0, Optional.empty());
        } catch (IOException e) {
            Log.e("SmartDumpsterApp_HTTPMethods", "Problemi con il risultato della richiesta GET HTTP");
            return Pair.create(0, Optional.empty());
        }
    }),
    PUT((c, p) -> {
        try {
            c.setRequestMethod("PUT");
            c.setDoOutput(true);
            if (p.isPresent()) {
                c.getOutputStream().write(p.get());
            }
            if (c.getResponseCode() == HttpURLConnection.HTTP_OK) {
                return Pair.create(c.getResponseCode(), Optional.of(c.getInputStream()));
            } else {
                Log.d("HTTPConnectionMethod", "Request result: " + c.getResponseCode());
                return Pair.create(c.getResponseCode(), Optional.empty());
            }
        } catch (ProtocolException e) {
            Log.e("SmartDumpsterApp_HTTPMethods", "Problemi con il protocollo HTTP");
            return Pair.create(0, Optional.empty());
        } catch (IOException e) {
            Log.e("SmartDumpsterApp_HTTPMethods", "Problemi con il risultato della comunicazione HTTP");
            return Pair.create(0, Optional.empty());
        }
    });

    private BiFunction<HttpURLConnection, Optional<byte[]>, Pair<Integer, Optional<InputStream>>> function;

    HTTPConnectionMethod(final BiFunction<HttpURLConnection, Optional<byte[]>, Pair<Integer, Optional<InputStream>>> function) {
        this.function = function;
    }

    /**
     * Executes an HTTP request.
     * @param connection the HTTPUrlConnection used to execute the request
     * @param payload the optional payload to be sent (only via POST)
     * @return the {@link InputStream} containing the server response if all went well, an empty {@link Optional} otherwise
     */
    public Pair<Integer, Optional<InputStream>> doRequest(final HttpURLConnection connection, final Optional<byte[]> payload) {
        return this.function.apply(connection, payload);
    }
}
