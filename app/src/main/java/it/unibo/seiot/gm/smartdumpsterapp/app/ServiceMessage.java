package it.unibo.seiot.gm.smartdumpsterapp.app;

/**
 * An enum representing the possible messages that can be sent to the service server.
 */
public enum ServiceMessage {
    GET_TOKEN("get_token"),
    START_DEPOSIT("start"),
    STOP_DEPOSIT("stop");

    private final String message;

    ServiceMessage(final String message) {
        this.message = message;
    }

    /**
     * Returns the string message associated to this {@link ServiceMessage}.
     * @return the string message
     */
    public String getMessage() {
        return this.message;
    }
}
