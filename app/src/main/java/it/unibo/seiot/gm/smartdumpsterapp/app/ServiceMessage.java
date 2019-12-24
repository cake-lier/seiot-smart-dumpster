package it.unibo.seiot.gm.smartdumpsterapp.app;

import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Optional;

/**
 * An enum representing the possible messages that can be sent to the service server.
 */
public enum ServiceMessage {
    GET_TOKEN("token", HTTPConnectionMethod.GET, ""),
    START_DEPOSIT("deposit", HTTPConnectionMethod.PUT, "{ \"deposit\": \"begin\" }"),
    STOP_DEPOSIT("deposit", HTTPConnectionMethod.PUT, "{ \"deposit\": \"end\" }");

    private static final String TAG = "SmartDumpsterApp_ServiceMessage";

    private final String path;
    private final HTTPConnectionMethod method;
    private final Optional<JSONObject> message;

    ServiceMessage(final String path, final HTTPConnectionMethod method, final String jsonMessage) {
        this.path = path;
        this.method = method;
        JSONObject json = null;
        try {
            json = new JSONObject(jsonMessage);
        } catch (JSONException e) {
            Log.e(TAG, "JSONObject creation failed");
        }
        this.message = Optional.ofNullable(json);
    }

    /**
     * Returns the JSON message associated to this {@link ServiceMessage}.
     * @return the JSON message
     */
    public Optional<JSONObject> getMessage() {
        return this.message;
    }

    /**
     * Returns the route on the server where to send the message.
     * @return the route name
     */
    public String getPath() {
        return this.path;
    }

    /**
     * Returns the method to use to send the eventual message to the server
     * @return the {@link HTTPConnectionMethod} to use
     */
    public HTTPConnectionMethod getMethod() {
        return this.method;
    }
}
