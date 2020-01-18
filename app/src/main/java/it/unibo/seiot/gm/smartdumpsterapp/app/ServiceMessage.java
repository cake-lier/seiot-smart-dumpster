package it.unibo.seiot.gm.smartdumpsterapp.app;

import android.util.Pair;

import org.json.JSONObject;

import java.util.Optional;
import java.util.function.Consumer;

public class ServiceMessage {

    private final ServiceMessageType type;
    private final JSONObject message;

    /**
     * Builds a new {@link ServiceMessage}.
     * @param type the type of the message being built
     * @param message the content on the message in json format
     */
    public ServiceMessage(final ServiceMessageType type, final JSONObject message) {
        this.type = type;
        this.message = message;
    }

    /**
     * Sends this {@link ServiceMessage} to the service, managing the result of the connection to the service with the given
     * resultManager.
     * @param resultManager a {@link Consumer} used to manage the result of the connection with the service
     */
    public void send(final Consumer<Optional<Pair<Integer, String>>> resultManager) {
        new SendMessageToServiceTask(resultManager).execute(this);
    }

    /**
     * @return the {@link ServiceMessageType} of this message
     */
    public ServiceMessageType getMessageType() {
        return this.type;
    }

    /**
     * @return the message in json format that this {@link ServiceMessage} contains
     */
    public JSONObject getMessage() {
        return this.message;
    }

}
