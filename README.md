# toml-java

**NOTE: THIS PROJECT IS HIGHLY WIP, THE BUILDSYSTEM IS INCOMPETE AND IT IS UNTESTED FOR MEMORY LEAKS AND CROSS-PLATFORM USAGE**

Java bindings (JNI) for [tomlc99](https://github.com/cktan/tomlc99).

If you would like to make changes to the bindings, you can use [this shell script](gen_headers.sh) to have javac generate the JNI headers (TODO: windows bat script).

Refer to [here](toml-java-bindings/src/test/java/io/github/neva1ack/toml/Main.java) for highly incomplete test suite and some basic examples. Please note the bindings implement more functions than used in the examples refer to [here](toml-java-bindings/src/main/java/io/github/neva1ack/toml) to see what's implemented.

Please be mindful if an object implements try-with-resources (aka AutoCloseable) as that means it needs to be used in a try-with-resources block in order to avoid a memory leak as it has data that needs to be freed after use. Alternatively the AutoCloseable#close() method can be called on these objects to manually free them.

P.S. don't forget to clone this repository recursively as tomlc99 is a submodule!
