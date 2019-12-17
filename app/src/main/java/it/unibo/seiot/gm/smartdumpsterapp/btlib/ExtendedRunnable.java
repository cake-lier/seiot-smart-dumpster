package it.unibo.seiot.gm.smartdumpsterapp.btlib;

public interface ExtendedRunnable extends Runnable {
    void write(byte[] bytes);
    void cancel();
}
