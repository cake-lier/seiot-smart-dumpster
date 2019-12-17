package it.unibo.seiot.gm.smartdumpsterapp.app;

import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.ProtocolException;
import java.util.Optional;
import java.util.function.BiFunction;

public enum HTTPConnectionMethods {
    GET((c, p) -> {
        try {
            c.setRequestMethod("GET");
            if (c.getResponseCode() == HttpURLConnection.HTTP_OK) {
                return Optional.of(c.getInputStream());
            } else {
                return Optional.empty();
            }
        } catch (ProtocolException e) {
            Log.e("Smart Dumpster App", "Problemi con il protocollo HTTP");
            return Optional.empty();
        } catch (IOException e) {
            Log.e("Smart Dumpster App", "Problemi con il risultato della comunicazione HTTP");
            return Optional.empty();
        }
    }),
    POST((c,p) -> {
        try {
            c.setRequestMethod("POST");
            c.setDoOutput(true);
            if (p.isPresent()) {
                c.getOutputStream().write(p.get());
            }
            if (c.getResponseCode() == HttpURLConnection.HTTP_OK) {
                return Optional.of(c.getInputStream());
            } else {
                return Optional.empty();
            }
        } catch (ProtocolException e) {
            Log.e("Smart Dumpster App", "Problemi con il protocollo HTTP");
            return Optional.empty();
        } catch (IOException e) {
            Log.e("Smart Dumpster App", "Problemi con il risultato della comunicazione HTTP");
            return Optional.empty();
        }
    });

    private BiFunction<HttpURLConnection, Optional<byte[]>, Optional<InputStream>> function;

    HTTPConnectionMethods(final BiFunction<HttpURLConnection, Optional<byte[]>, Optional<InputStream>> function) {
        this.function = function;
    }

    public Optional<InputStream> doRequest(final HttpURLConnection connection, final Optional<byte[]> payload) {
        return this.function.apply(connection, payload);
    }
}
