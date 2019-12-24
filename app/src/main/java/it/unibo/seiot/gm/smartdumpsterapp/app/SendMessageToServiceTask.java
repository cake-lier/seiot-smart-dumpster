package it.unibo.seiot.gm.smartdumpsterapp.app;

import android.os.AsyncTask;
import android.util.Log;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.charset.Charset;
import java.util.Arrays;
import java.util.Optional;

/**
 * An {@link AsyncTask} used for sending messages to the service server.
 */
public class SendMessageToServiceTask extends AsyncTask<ServiceMessage, Void, Boolean> {

    private static final String TAG = "SmartDumpsterApp_HTTPConnection";
    private static final String BASE_URL = "http://www.google.com"; // TODO:

    /**
     * Builds a new {@link SendMessageToServiceTask}.
     */
    public SendMessageToServiceTask() {
    }

    @Override
    protected Boolean doInBackground(final ServiceMessage... messages) {
        // TODO: put conn.disconnect() to free resources
        Log.d(TAG, "Creating HTTPUrlConnection");
        return Arrays.stream(messages)
                     .map(m -> {
                         try {
                             return m.getMethod()
                                     .doRequest((HttpURLConnection) new URL(BASE_URL + m.getPath()).openConnection(),
                                                m.getMessage()
                                                 .map(j -> j.toString()
                                                            .getBytes(Charset.forName("UTF-8"))));
                         } catch (final IOException e) {
                             Log.e(TAG, e.getMessage());
                         }
                         return Optional.empty();
                     })
                     .allMatch(Optional::isPresent);
        // this way there is no way to understand which message didn't work
    }
}
