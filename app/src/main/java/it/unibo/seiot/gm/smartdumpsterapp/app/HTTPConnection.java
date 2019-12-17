package it.unibo.seiot.gm.smartdumpsterapp.app;

import android.os.AsyncTask;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Arrays;
import java.util.Optional;
import java.util.function.Consumer;

public class HTTPConnection extends AsyncTask<String, Void, String> {

    private final URL url;
    private final HTTPConnectionMethods method;
    private final Consumer<String> manageResult;

    public HTTPConnection(final String url,
                          final HTTPConnectionMethods method,
                          final Consumer<String> manageResult) throws MalformedURLException {
        this.url = new URL(url);
        this.method = method;
        this.manageResult = manageResult;
    }
    @Override
    protected String doInBackground(final String... messages) {
        try {
            // TODO: put conn.disconnect() to free resources
            final HttpURLConnection conn = (HttpURLConnection) this.url.openConnection();
            if (messages.length > 0) {
                Arrays.stream(messages)
                      .map(m -> this.method.doRequest(conn, Optional.of(m.getBytes())))
                      .filter(Optional::isPresent)
                      .map(Optional::get)
                      .map(this::readStream)
                      .forEach(e -> {}); // TODO: what to do here
            } else {
                final Optional<InputStream> result = this.method.doRequest(conn, Optional.empty());
                if (result.isPresent()) {
                    return readStream(result.get());
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return ""; // TODO:
    }

    @Override
    protected void onPostExecute(final String result) {
        this.manageResult.accept(result); // executed on Main Thread
    }

    private String readStream(final InputStream in) {
        // TODO:
        return "";
    }
}
