/* Authors: Matteo Castellucci, Giorgia Rondinini */
package it.unibo.seiot.smartdumpster.model;

/**
 * An enum representing the possible status codes of the HTTP protocol.
 */
public enum HttpStatus {
    /**
     * An {@link HttpStatus} signalling that the request was badly formatted.
     */
    BAD_REQUEST(400),
    /**
     * An {@link HttpStatus} signalling that the request was successfully processed.
     */
    OK(200),
    /**
     * An {@link HttpStatus} signalling that the client that made the request wasn't authorized.
     */
    FORBIDDEN(403),
    /**
     * An {@link HttpStatus} signalling that something unexpected happened in the web server.
     */
    INTERNAL_SERVER_ERROR(500);

    private final int code;

    HttpStatus(final int code) {
        this.code = code;
    }
    /**
     * Returns the HTTP protocol status code associated with this status.
     * @return the HTTP protocol status code associated with this status
     */
    public int getCode() {
        return this.code;
    }
}
