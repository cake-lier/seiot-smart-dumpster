package it.unibo.seiot.gm.smartdumpsterapp.app;

import android.os.AsyncTask;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Arrays;
import java.util.Optional;

public class SendMessageToServiceTask extends AsyncTask<String, Void, Boolean> {

    private static final String TAG = "SmartDumpsterApp_HTTPConnection";
    private static final String BASE_URL = "http://www.google.com"; // TODO:

    public SendMessageToServiceTask() {
    }

    @Override
    protected Boolean doInBackground(final String... strings) {
        try {
            // TODO: put conn.disconnect() to free resources
            Log.d(TAG, "Creating HTTPUrlConnection");
            final HttpURLConnection conn = (HttpURLConnection) new URL(BASE_URL).openConnection();
            return Arrays.stream(strings)
                         .map(String::getBytes)
                         .map(Optional::of)
                         .map(p ->HTTPConnectionMethods.POST.doRequest(conn, p))
                         .allMatch(Optional::isPresent);
            // this way there is no way to understand which message didn't work
        } catch (IOException e) {
            Log.e(TAG, e.getMessage());
        }
        return false;
    }
}
