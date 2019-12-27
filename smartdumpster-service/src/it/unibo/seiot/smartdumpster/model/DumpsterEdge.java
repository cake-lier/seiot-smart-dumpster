package it.unibo.seiot.smartdumpster.model;

/**
 * 
 */
public interface DumpsterEdge {
    /**
     * 
     * @return a
     */
    boolean isStateAvailable();
    /**
     * 
     * @param available a
     */
    void setStateAvailable(boolean available);
    /**
     * 
     * @return a
     */
    boolean hasDepositBegun();
    /**
     * 
     */
    void beginDeposit();
    /**
     * 
     */
    void endDeposit();
    /**
     * 
     * @return a
     */
    boolean hasLastDepositEarlyEnded();
    /**
     * 
     * @param earlyEnded a
     */
    void setEarlyEnd(boolean earlyEnded);
}
