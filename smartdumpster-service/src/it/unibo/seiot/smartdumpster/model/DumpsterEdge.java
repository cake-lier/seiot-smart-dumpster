/* Authors: Matteo Castellucci, Giorgia Rondinini */
package it.unibo.seiot.smartdumpster.model;

/**
 * An interface representing the Edge component of the Smart Dumpster project.
 */
public interface DumpsterEdge {
    /**
     * Returns whether the Edge is in its available or unavailable state.
     * @return true if the Edge is available, false otherwise
     */
    boolean isStateAvailable();
    /**
     * Sets the Edge state.
     * @param available true if the state must be set to available, false if it must be set to unavailable.
     */
    void setStateAvailable(boolean available);
    /**
     * Returns whether there is a deposit in progress.
     * @return true if there is a deposit in progress, false otherwise.
     */
    boolean hasDepositBegun();
    /**
     * Begins a deposit.
     */
    void beginDeposit();
    /**
     * Ends the current deposit.
     */
    void endDeposit();
    /**
     * Returns if the last deposit managed by the Edge terminated prematurely.
     * @return true is the last deposit ended prematurely, false otherwise
     */
    boolean hasLastDepositEarlyEnded();
    /**
     * Sets whether the last deposit has ended prematurely. If so, and if there is a deposit in progress, terminates the deposit.
     * @param earlyEnded whether the last deposit terminated early or not
     */
    void setEarlyEnd(boolean earlyEnded);
}
