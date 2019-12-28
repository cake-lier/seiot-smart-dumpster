package it.unibo.seiot.gm.smartdumpsterapp.app;

import org.json.JSONObject;

import java.util.function.Consumer;

public class ServiceMessage {

    private final ServiceMessageType type;
    private final JSONObject message;

    public ServiceMessage(final ServiceMessageType type, final JSONObject message) {
        this.type = type;
        this.message = message;
    }

    public void send(final Consumer<JSONObject> resultManager) {
        new SendMessageToServiceTask(resultManager).execute(this);
    }

    public ServiceMessageType getMessageType() {
        return this.type;
    }

    public JSONObject getMessage() {
        return this.message;
    }

}
