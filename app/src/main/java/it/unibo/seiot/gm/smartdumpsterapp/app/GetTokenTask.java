package it.unibo.seiot.gm.smartdumpsterapp.app;

import android.os.AsyncTask;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Optional;
import java.util.function.Consumer;

public class GetTokenTask extends AsyncTask<Void, Void, String> {

    private static final String TAG = "SmartDumpsterApp_HTTPConnection";
    private static final String REQUEST_URL = "http://www.google.com"; // TODO:

    private final Consumer<String> resultManager;

    public GetTokenTask(final Consumer<String> resultManager) {
        this.resultManager = resultManager;
    }

    @Override
    protected String doInBackground(final Void... voids) {
        try {
            // TODO: put conn.disconnect() to free resources
            Log.d(TAG, "Creating HTTPUrlConnection");
            final HttpURLConnection conn = (HttpURLConnection) new URL(REQUEST_URL).openConnection();
            final Optional<InputStream> in = HTTPConnectionMethods.GET.doRequest(conn, Optional.empty());
            if (in.isPresent()) {
                return readStream(in.get());
            }
        } catch (IOException e) {
            Log.e(TAG, e.getMessage());
        }
        return ""; // TODO:
    }

    @Override
    protected void onPostExecute(final String result) {
        this.resultManager.accept(result); // executed on Main Thread
    }

    private String readStream(final InputStream in) {
        // TODO: maybe move it somewhere common?
        try (final BufferedReader br = new BufferedReader(new InputStreamReader(in))) {
            final StringBuilder sb = new StringBuilder();
            String s = br.readLine();
            while (s != null) {
                sb.append(s);
                s = br.readLine();
            }
            return sb.toString();
        } catch (final IOException e) {
            Log.e(TAG, e.getMessage());
        }
        return "";
    }
}
