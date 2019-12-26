package it.unibo.seiot.gm.smartdumpsterapp.app;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class ServiceMessageBuilder {
    private final static String TOKEN_KEY = "token";
    private final static String DEPOSIT_KEY = "deposit";

    private final ServiceMessageType type;
    private final Map<String, String> values;

    public ServiceMessageBuilder(final ServiceMessageType messageType) {
        this.type = messageType;
        this.values = new HashMap<>();
    }

    public ServiceMessageBuilder setToken(final String token) {
        return this.setKeyValue(TOKEN_KEY, token);
    }

    public ServiceMessageBuilder setDepositPhase(final String phase) {
        return this.setKeyValue(DEPOSIT_KEY, phase);
    }

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
