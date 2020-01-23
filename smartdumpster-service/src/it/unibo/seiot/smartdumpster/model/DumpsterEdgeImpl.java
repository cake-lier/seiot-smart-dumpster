/* Authors: Matteo Castellucci, Giorgia Rondinini */
package it.unibo.seiot.smartdumpster.model;

/**
 * An implementation of {@link DumpsterEdge}.
 */
public class DumpsterEdgeImpl implements DumpsterEdge {
    private boolean lastDepositEarlyEnded;
    private boolean depositBegun;
    private boolean isAvailable;

    /**
     * Builds a new {@link DumpsterEdgeImpl}.
     */
    public DumpsterEdgeImpl() {
        this.lastDepositEarlyEnded = false;
        this.depositBegun = false;
        this.isAvailable = true;
    }
    /**
     * {@inheritDoc}
     */
    @Override
    public synchronized boolean isStateAvailable() {
        return this.isAvailable;
    }
    /**
     * {@inheritDoc}
     */
    @Override
    public synchronized void setStateAvailable(final boolean available) {
        this.isAvailable = available;
    }
    /**
     * {@inheritDoc}
     */
    @Override
    public boolean hasDepositBegun() {
        return this.depositBegun;
    }
    /**
     * {@inheritDoc}
     */
    @Override
    public void beginDeposit() {
        this.depositBegun = true;
    }
    /**
     * {@inheritDoc}
     */
    @Override
    public void endDeposit() {
        this.depositBegun = false;
    }
    /**
     * {@inheritDoc}
     */
    @Override
    public boolean hasLastDepositEarlyEnded() {
        return this.lastDepositEarlyEnded;
    }
    /**
     * {@inheritDoc}
     */
    @Override
    public void setEarlyEnd(final boolean earlyEnded) {
        this.lastDepositEarlyEnded = earlyEnded;
        if (earlyEnded) {
            this.isAvailable = false;
        }
    }
}
