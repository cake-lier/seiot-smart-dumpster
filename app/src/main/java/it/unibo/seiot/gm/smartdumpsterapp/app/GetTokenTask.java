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

/**
 * {@link AsyncTask} used for getting a token from the service
 */
public class GetTokenTask extends AsyncTask<Void, Void, String> {
    private static final String TAG = "SmartDumpsterApp_HTTPConnection";
    private static final String BASE_URL = "http://www.google.com/"; // TODO:

    private final Consumer<String> resultManager;

    /**
     * Builds a new {@link GetTokenTask}.
     * @param resultManager a {@link Consumer} used for managing the result of the {@link GetTokenTask}
     */
    public GetTokenTask(final Consumer<String> resultManager) {
        this.resultManager = resultManager;
    }

    @Override
    protected String doInBackground(final Void... voids) {
        try {
            Log.d(TAG, "Creating HTTPUrlConnection");
            final HttpURLConnection conn
                    = (HttpURLConnection) new URL(BASE_URL + ServiceMessage.GET_TOKEN.getMessage()).openConnection();
            final Optional<InputStream> in = HTTPConnectionMethods.GET.doRequest(conn, Optional.empty());
            conn.disconnect();
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
