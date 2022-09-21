cmake_minimum_required(VERSION 3.24)
project(toml_java_native
        VERSION 0.1.0
        LANGUAGES C)
# C99 ISO standard
set(CMAKE_C_STANDARD 99)
# Require standard
set(CMAKE_C_STANDARD_REQUIRED ON)
# set release build
set(CMAKE_BUILD_TYPE Release)
# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
# find JNI from JDK
find_package(JNI REQUIRED)
# create shared object from src/
include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(${PROJECT_NAME} SHARED
        tomlc99/toml.c
        src/toml_jni_common.c
        src/toml_array_jni.c
        src/toml_table_jni.c)
# include toml
target_include_directories(${PROJECT_NAME} PRIVATE tomlc99)
# link with JNI
target_link_libraries(${PROJECT_NAME} PRIVATE JNI::JNI)
