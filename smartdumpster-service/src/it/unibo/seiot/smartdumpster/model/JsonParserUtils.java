package it.unibo.seiot.smartdumpster.model;

import java.util.Map;
import java.util.Set;

import io.vertx.core.json.JsonObject;

/**
 * A collection of utilities for parsing JSON objects.
 */
public final class JsonParserUtils {
    private JsonParserUtils() { }
    /**
     * Takes a {@link JsonObject}, checks if it contains the given key, if so gets the corresponding value,
     * if said value is of type T checks if is contained in values.
     * @param <T> the type of the value that should be contained in the JsonObject
     * @param json the {@link JsonObject} to parse
     * @param key the key that should be contained in the {@link JsonObject}
     * @param fieldType a {@link Class} object of the type the value contained in the {@link JsonObject} should be
     * @param values the possible values the value contained in the {@link JsonObject} should assume
     * @return the value contained in the {@link JsonObject}
     */
    public static <T extends Object> boolean hasJsonCorrectField(final JsonObject json,
                                                                 final String key,
                                                                 final Class<T> fieldType,
                                                                 final Set<T> values) {
        return json.stream()
                   .filter(e -> e.getKey().equals(key))
                   .map(Map.Entry::getValue)
                   .filter(v -> v.getClass().equals(fieldType))
                   .map(fieldType::cast)
                   .anyMatch(c -> values.isEmpty() || values.contains(c));
    }
}
