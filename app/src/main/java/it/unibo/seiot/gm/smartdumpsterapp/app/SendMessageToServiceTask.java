package it.unibo.seiot.gm.smartdumpsterapp.app;

import android.os.AsyncTask;
import android.util.Log;
import android.util.Pair;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.charset.Charset;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.Scanner;
import java.util.function.Consumer;
import java.util.stream.Collectors;

/**
 * An {@link AsyncTask} used for sending messages to the service server.
 */
public class SendMessageToServiceTask extends AsyncTask<ServiceMessage, Void, List<Optional<Pair<Integer, String>>>> {

    private static final String TAG = "SmartDumpsterApp_HTTPConnection";
    private static final String BASE_URL = "http://192.168.43.201:8080/"; // TODO:
    private static final int TIMEOUT = 5000;

    private final Consumer<Optional<Pair<Integer, String>>> resultManager;

    /**
     * Builds a new {@link SendMessageToServiceTask}.
     * @param resultManager a {@link Consumer} used for managing the result of the {@link SendMessageToServiceTask}
     */
    public SendMessageToServiceTask(final Consumer<Optional<Pair<Integer, String>>> resultManager) {
        this.resultManager = resultManager;
    }

    @Override
    protected List<Optional<Pair<Integer, String>>> doInBackground(final ServiceMessage... messages) {
        Log.d(TAG, "Creating HTTPUrlConnection");
        return Arrays.stream(messages)
                     .map(m -> {
                         HttpURLConnection conn = null;
                         Optional<Pair<Integer, Optional<InputStream>>> result = Optional.empty();
                         try {
                             conn = (HttpURLConnection) new URL(BASE_URL + m.getMessageType().getPath()).openConnection();
                             conn.setConnectTimeout(TIMEOUT);
                             if (m.getMessage().length() > 0) {
                                 conn.setRequestProperty("Content-Type", "application/json");
                             }
                             result =  Optional.of(m.getMessageType()
                                                    .getMethod()
                                                    .doRequest(conn, m.getMessage().length() > 0
                                                                        ? Optional.of(m.getMessage()
                                                                                       .toString()
                                                                                       .getBytes(Charset.forName("UTF-8")))
                                                                        : Optional.empty()));
                         } catch (final IOException e) {
                             Log.e(TAG, e.getMessage());
                         } finally {
                             if (Objects.nonNull(conn)) {
                                 conn.disconnect();
                             }
                             Log.d(TAG, "Connection result: " + result.toString());
                         }
                         return result;
                     })
                     .filter(Optional::isPresent)
                     .map(Optional::get)
                     .map(p -> {
                         if (p.first != 0 && p.second.isPresent()) {
                             return Pair.create(p.first, this.readStream(p.second.get()));
                         } else if (p.first >= 200 && p.first < 300) {
                             return Pair.create(p.first, "");
                         } else {
                             Log.d(TAG, "Error code: " + p.first);
                             return null;
                         }
                     })
                     .map(Optional::ofNullable)
                     .collect(Collectors.toList());
    }

    @Override
    protected void onPostExecute(final List<Optional<Pair<Integer, String>>> result) {
        result.forEach(this.resultManager); // executed on Main Thread
    }

    private String readStream(final InputStream in) {
        Scanner s = new Scanner(in).useDelimiter("\\A");
        return s.hasNext() ? s.next() : "";
    }
}
