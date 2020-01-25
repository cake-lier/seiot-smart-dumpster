/* Authors: Matteo Castellucci, Giorgia Rondinini */
package it.unibo.seiot.gm.smartdumpsterapp.btlib;

public interface CommChannel {
    void close();

    void registerListener(Listener listener);

    void removeListener(Listener listener);

    String getRemoteDeviceName();

    void sendMessage(String message);

    interface Listener {
        void onMessageReceived(String receivedMessage);
        void onMessageSent(String sentMessage);
    }
}
