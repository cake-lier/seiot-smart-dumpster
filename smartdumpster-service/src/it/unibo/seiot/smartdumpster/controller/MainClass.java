/**
 * 
 */
package it.unibo.seiot.smartdumpster.controller;

import io.vertx.core.Vertx;
import it.unibo.seiot.smartdumpster.model.ServiceHttpServer;

/**
 * 
 */
public final class MainClass {
    /**
     * @param args Unused.
     */
    public static void main(final String[] args) {
        final Vertx vertx = Vertx.vertx();
        vertx.deployVerticle(new ServiceHttpServer());
    }
    /*
     * 
     */
    private MainClass() { }
}
