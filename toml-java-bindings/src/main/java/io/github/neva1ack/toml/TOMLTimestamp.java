package io.github.neva1ack.toml;

public final class TOMLTimestamp implements AutoCloseable {

    private final long handle;

    public TOMLTimestamp(long handle) {
        this.handle = handle;
    }

    public native int getYear();
    public native int getMonth();
    public native int getDay();
    public native int getHour();
    public native int getMinute();
    public native int getSecond();
    public native int getMilliSecond();
    public native boolean isZeroedTime();

    @Override
    public void close() {
        free();
    }

    private native void free();
}
