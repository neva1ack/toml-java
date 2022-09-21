#!/bin/sh
# make directory to output classes to
mkdir temp_classes
# generate headers with javac -h (javah is deprecated), match all .java files in toml-java-bindings/src
# write classes to temp_classes (they are not needed, maybe these is a better solution)
javac -d temp_classes -h toml-java-native/include $(find toml-java-bindings/src -regex ".+\.java")
# remove classes
rm -rf temp_classes