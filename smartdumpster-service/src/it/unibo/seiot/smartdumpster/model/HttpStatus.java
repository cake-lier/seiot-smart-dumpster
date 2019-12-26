package it.unibo.seiot.smartdumpster.model;

/**
 * 
 */
public enum HttpStatus {
    /**
     * 
     */
    BAD_REQUEST(400),
    /**
     * 
     */
    OK(200),
    /**
     * 
     */
    FORBIDDEN(403),
    /**
     * 
     */
    INTERNAL_SERVER_ERROR(500);

    private final int code;

    /*
     * 
     */
    HttpStatus(final int code) {
        this.code = code;
    }
    /**
     * 
     * @return the HTTP protocol status code associated with this status
     */
    public int getCode() {
        return this.code;
    }
}
