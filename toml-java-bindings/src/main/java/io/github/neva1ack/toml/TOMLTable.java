package io.github.neva1ack.toml;

import java.nio.file.Path;

public final class TOMLTable implements AutoCloseable {

    private final long handle;

    private TOMLTable(long handle) {
        this.handle = handle;
    }

    public static void loadNative(Path nativePath) {
        System.load(nativePath.toAbsolutePath().toString());
    }

    @Override
    public void close() {
        free();
    }

    public static native TOMLTable parseFile(String filename);
    public static native TOMLTable parse(String table);
    private native void free();
    public native String getKeyIn(int keyidx);
    public native boolean isKeyExists(String key);
    public native String getStringIn(String key);
    public native boolean getBooleanIn(String key);
    public native long getIntIn(String key);
    public native double getDoubleIn(String key);
    public native TOMLTimestamp getTimestampIn(String key);
    public native TOMLArray getArrayIn(String key);
    public native TOMLTable getTableIn(String key);
}
