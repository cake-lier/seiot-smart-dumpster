package it.unibo.seiot.gm.smartdumpsterapp.app;

public enum ServiceMessage {
    GET_TOKEN("get_token"),
    START_DEPOSIT("start"),
    STOP_DEPOSIT("stop");

    private final String message;

    ServiceMessage(final String message) {
        this.message = message;
    }

    public String getMessage() {
        return this.message;
    }
}
