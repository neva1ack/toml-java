package io.github.neva1ack.toml;

public final class TOMLArray {

    private final long handle;

    private TOMLArray(long handle) {
        this.handle = handle;
    }

    public native int getSize();
    public native String getStringAt(int idx);
    public native boolean getBooleanAt(int idx);
    public native long getIntAt(int idx);
    public native double getDoubleAt(int idx);
    public native TOMLTimestamp getTimestampAt(int idx);
    public native TOMLArray getArrayAt(int idx);
    public native TOMLTable getTableAt(int idx);
}
