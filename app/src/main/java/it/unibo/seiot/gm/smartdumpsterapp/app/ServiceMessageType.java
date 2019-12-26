package it.unibo.seiot.gm.smartdumpsterapp.app;

import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;

/**
 * An enum representing the possible messages that can be sent to the service server.
 */
public enum ServiceMessageType {
    GET_TOKEN("token", HTTPConnectionMethod.GET, new HashSet<>()),
    START_DEPOSIT("deposit", HTTPConnectionMethod.PUT, new HashSet<String>(Arrays.asList("deposit", "token"))),
    STOP_DEPOSIT("deposit", HTTPConnectionMethod.PUT, new HashSet<String>(Arrays.asList("deposit", "token")));

    private static final String TAG = "SmartDumpsterApp_ServiceMessage";

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

    public Collection<String> getRequiredKeys() {
        return Collections.unmodifiableCollection(this.requiredKeys);
    }
}
