package it.unibo.seiot.smartdumpster.model;

/**
 * 
 */
public class DumpsterEdgeImpl implements DumpsterEdge {
    private boolean lastDepositEarlyEnded;
    private boolean hasDepositBegun;
    private boolean isAvailable;

    /**
     * 
     */
    public DumpsterEdgeImpl() {
        this.lastDepositEarlyEnded = false;
        this.hasDepositBegun = false;
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
        return this.hasDepositBegun;
    }
    /**
     * {@inheritDoc}
     */
    @Override
    public void beginDeposit() {
        this.hasDepositBegun = true;
    }
    /**
     * {@inheritDoc}
     */
    @Override
    public void endDeposit() {
        this.hasDepositBegun = false;
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
            this.endDeposit();
            this.isAvailable = false;
        }
    }
}
