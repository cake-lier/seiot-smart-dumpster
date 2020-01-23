/* Authors: Matteo Castellucci, Giorgia Rondinini */
/**
 * 
 */
package it.unibo.seiot.smartdumpster.controller;

import io.vertx.core.Vertx;
import it.unibo.seiot.smartdumpster.model.ServiceHttpServer;

/**
 * Main class of the Service part of the Smart Dumpster project. It works as both a web server,
 * in its interactions with the Android App, the Dashboard and the Edge part of the project,
 * and as a web client, in some of its interactions with the Edge.
 */
public final class MainClass {
    /**
     * @param args Unused.
     */
    public static void main(final String[] args) {
        final Vertx vertx = Vertx.vertx();
        vertx.deployVerticle(new ServiceHttpServer());
    }
}
