package it.unibo.seiot.gm.smartdumpsterapp.app;

import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;

/**
 * An enum representing the possible messages that can be sent to the service server.
 */
public enum ServiceMessageType {
    /**
     * The type of a message used to request a token from the service.
     */
    GET_TOKEN("token", HTTPConnectionMethod.GET, new HashSet<>()),
    /**
     * The type of message used to signal to the service the start of a deposit.
     */
    START_DEPOSIT("deposit", HTTPConnectionMethod.PUT, new HashSet<>(Arrays.asList("deposit", "token"))),
    /**
     * The type of a message used to signal to the service the end of a deposit.
     */
    STOP_DEPOSIT("deposit", HTTPConnectionMethod.PUT, new HashSet<>(Arrays.asList("deposit", "token"))),
    /**
     * The type of a message used to signal to the service that a deposit is still going on.
     */
    KEEP_DEPOSITING("deposit", HTTPConnectionMethod.PUT, new HashSet<>(Arrays.asList("deposit", "token")));

    private final String path;
    private final HTTPConnectionMethod method;
    private final Collection<String> requiredKeys;

    ServiceMessageType(final String path, final HTTPConnectionMethod method, final Collection<String> requiredKeys) {
        this.path = path;
        this.method = method;
        this.requiredKeys = requiredKeys;
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

    /**
     * Returns the keys required to be in a {@link ServiceMessage} of this type
     * @return the keys that must have a value in a {@link ServiceMessage} of this {@link ServiceMessageType}
     */
    public Collection<String> getRequiredKeys() {
        return Collections.unmodifiableCollection(this.requiredKeys);
    }
}
