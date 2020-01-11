package it.unibo.seiot.gm.smartdumpsterapp.app;

import android.os.AsyncTask;
import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.Scanner;
import java.util.function.Consumer;
import java.util.stream.Collectors;

/**
 * An {@link AsyncTask} used for sending messages to the service server.
 */
public class SendMessageToServiceTask extends AsyncTask<ServiceMessage, Void, List<Optional<JSONObject>>> {

    private static final String TAG = "SmartDumpsterApp_HTTPConnection";
    private static final String BASE_URL = "http://192.168.43.201:8080/"; // TODO:

    private final Consumer<Optional<JSONObject>> resultManager;

    /**
     * Builds a new {@link SendMessageToServiceTask}.
     * @param resultManager a {@link Consumer} used for managing the result of the {@link SendMessageToServiceTask}
     */
    public SendMessageToServiceTask(final Consumer<Optional<JSONObject>> resultManager) {
        this.resultManager = resultManager;
    }

    @Override
    protected List<Optional<JSONObject>> doInBackground(final ServiceMessage... messages) {
        Log.d(TAG, "Creating HTTPUrlConnection");
        return Arrays.stream(messages)
                     .map(m -> {
                         HttpURLConnection conn = null;
                         Optional<InputStream> result = Optional.empty();
                         try {
                             conn = (HttpURLConnection) new URL(BASE_URL + m.getMessageType().getPath()).openConnection();
                             result =  m.getMessageType()
                                        .getMethod()
                                        .doRequest(conn, m.getMessage().length() > 0
                                                            ? Optional.of(m.getMessage().toString().getBytes(Charset.forName("UTF-8")))
                                                            : Optional.empty());
                         } catch (final IOException e) {
                             Log.e(TAG, e.getMessage());
                         } finally {
                             if (Objects.nonNull(conn)) {
                                 conn.disconnect();
                             }
                             Log.d(TAG, "Connection result: " + result.toString());
                             return result;
                         }
                     })
                     .filter(Optional::isPresent)
                     .map(Optional::get)
                     .map(this::readStream)
                     .map(s -> {
                         try {
                             return new JSONObject(s);
                         } catch (final JSONException e) {
                             Log.e(TAG, e.getMessage());
                             return null;
                         }
                     })
                     .map(Optional::ofNullable)
                     .collect(Collectors.toList());
    }

    @Override
    protected void onPostExecute(final List<Optional<JSONObject>> result) {
        result.forEach(this.resultManager); // executed on Main Thread
    }

    private String readStream(final InputStream in) {
        Scanner s = new Scanner(in).useDelimiter("\\A");
        return s.hasNext() ? s.next() : "";
    }
}
