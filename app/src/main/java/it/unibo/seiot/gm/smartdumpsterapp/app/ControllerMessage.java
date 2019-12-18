package it.unibo.seiot.gm.smartdumpsterapp.app;

public enum ControllerMessage {
    TRASH_1_SET_MESSAGE("A"),
    TRASH_2_SET_MESSAGE("B"),
    TRASH_3_SET_MESSAGE("C"),
    START_DEPOSIT("O"),
    STOP_DEPOSIT("E");

    private final String message;

    ControllerMessage(final String message) {
        this.message = message;
    }

    public String getMessage() {
        return this.message;
    }
}
