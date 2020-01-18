package it.unibo.seiot.gm.smartdumpsterapp.app;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class ServiceMessageBuilder {
    private final static String TOKEN_KEY = "token";
    private final static String DEPOSIT_KEY = "deposit";

    private final ServiceMessageType type;
    private final Map<String, String> values;

    /**
     * Builds a new {@link ServiceMessageBuilder}.
     * @param messageType the type of the {@link ServiceMessage} this builder will be used to build
     */
    public ServiceMessageBuilder(final ServiceMessageType messageType) {
        this.type = messageType;
        this.values = new HashMap<>();
    }

    /**
     * Sets the token to send to the service.
     * @param token the token to send to the service
     * @return this {@link ServiceMessageBuilder}
     */
    public ServiceMessageBuilder setToken(final String token) {
        return this.setKeyValue(TOKEN_KEY, token);
    }

    /**
     * Sets the deposit phase the {@link ServiceMessage} built will refer to
     * @param phase the phase of the service that will be communicated to the service.
     * @return this {@link ServiceMessageBuilder}
     */
    public ServiceMessageBuilder setDepositPhase(final String phase) {
        return this.setKeyValue(DEPOSIT_KEY, phase);
    }

    /**
     * Builds a {@link ServiceMessage} with the previously set characteristics.
     * Can be used more than once to construct copies of the same {@link ServiceMessage}.
     * @return the {@link ServiceMessage} built
     * @throws IllegalStateException if not all the fields for the given {@link ServiceMessageType} have been set
     */
    public ServiceMessage build() throws IllegalStateException {
        if (this.values.keySet().containsAll(this.type.getRequiredKeys())) {
            return new ServiceMessage(this.type, new JSONObject(this.values));
        } else {
            throw new IllegalStateException("Not all the required fields of the message have been set");
        }
    }

    private ServiceMessageBuilder setKeyValue(final String key, final String value) {
        this.values.put(key, value);
        return this;
    }
}
