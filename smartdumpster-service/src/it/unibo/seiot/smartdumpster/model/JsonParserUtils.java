package it.unibo.seiot.smartdumpster.model;

import java.util.Set;

import io.vertx.core.json.JsonObject;

/**
 * 
 */
public final class JsonParserUtils {
    /*
     * 
     */
    private JsonParserUtils() { }
    /**
     * 
     * @param <T> a
     * @param json a
     * @param key a
     * @param fieldType a
     * @param values a
     * @return a
     */
    public static <T extends Object> boolean hasJsonCorrectField(final JsonObject json,
                                                                 final String key,
                                                                 final Class<T> fieldType,
                                                                 final Set<T> values) {
        return json.stream()
                   .filter(e -> e.getKey().equals(key))
                   .map(p -> p.getValue())
                   .filter(v -> v.getClass().equals(fieldType))
                   .map(t -> fieldType.cast(t))
                   .anyMatch(c -> values.isEmpty() || values.contains(c));
    }
}
