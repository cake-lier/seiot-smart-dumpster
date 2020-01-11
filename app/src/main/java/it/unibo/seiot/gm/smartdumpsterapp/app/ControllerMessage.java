package it.unibo.seiot.gm.smartdumpsterapp.app;

/**
 * An enum representing the messages that can be received or sent from the Arduino controller.
 */
public enum ControllerMessage {
    /**
     * A message representing the first type of trash.
     */
    TRASH_1_SET_MESSAGE("A"),
    /**
     * A message representing the second type of trash.
     */
    TRASH_2_SET_MESSAGE("B"),
    /**
     * A message representing the third type of trash.
     */
    TRASH_3_SET_MESSAGE("C"),
    /**
     * A message representing the start of the deposit.
     */
    START_DEPOSIT("S"),
    /**
     * A message representing the end of the deposit.
     */
    STOP_DEPOSIT("E"),
    /**
     * A message representing the request to keep open the dumpster.
     */
    KEEP_OPEN_MESSAGE("K");

    private final String message;

    ControllerMessage(final String message) {
        this.message = message;
    }

    /**
     * Returns the string message associated to this {@link ControllerMessage}.
     * @return the string message
     */
    public String getMessage() {
        return this.message;
    }
}
