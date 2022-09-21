package io.github.neva1ack.toml;

import java.nio.file.Paths;

public class Main {

    private static void assertTrue(boolean value, String message) {
        if (!value)
            throw new IllegalStateException(message);
    }

    public static void main(String[] args) {
        TOMLTable.loadNative(Paths.get("toml-java-native/build/libtoml_java_native.so"));

        try (TOMLTable table = TOMLTable.parseFile("toml-java-native/tomlc99/sample.toml")) {
            assertTrue("server".equals(table.getKeyIn(0)),
                    "getKeyIn(0): missing [server]");
            assertTrue(table.isKeyExists("server"),
                    "isKeyExists(\"server\"): missing [server]");
            TOMLTable server = table.getTableIn("server");
            assertTrue("example.com".equals(server.getStringIn("host")),
                    "server.getStringIn(\"host\"): != \"host\"");
            TOMLArray array = server.getArrayIn("port");
            assertTrue(array.getSize() == 3, "server.getArrayIn(\"port\"): size != 3");
            assertTrue(array.getIntAt(0) == 8080, "array.getIntAt(0): != 8080");
            assertTrue(array.getIntAt(1) == 8181, "array.getIntAt(0): != 8181");
            assertTrue(array.getIntAt(2) == 8282, "array.getIntAt(0): != 8282");
        }
    }

}
