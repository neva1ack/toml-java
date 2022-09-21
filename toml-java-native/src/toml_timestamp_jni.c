#include <io_github_neva1ack_toml_TOMLTimestamp.h>
#include <stdlib.h>
#include <toml.h>
#include <toml_jni_common.h>

JNIEXPORT jint JNICALL Java_io_github_neva1ack_toml_TOMLTimestamp_getYear(
    JNIEnv *env, jobject timestamp) {
    toml_timestamp_t *timestamp_ptr =
        (toml_timestamp_t *)toml_handle_to_ptr(env, timestamp);
    if (!timestamp_ptr || !timestamp_ptr->year)
        goto error;
    return *timestamp_ptr->year;
error:
    return 0;
}

JNIEXPORT jint JNICALL Java_io_github_neva1ack_toml_TOMLTimestamp_getMonth(
    JNIEnv *env, jobject timestamp) {
    toml_timestamp_t *timestamp_ptr =
        (toml_timestamp_t *)toml_handle_to_ptr(env, timestamp);
    if (!timestamp_ptr || !timestamp_ptr->month)
        goto error;
    return *timestamp_ptr->month;
error:
    return 0;
}

JNIEXPORT jint JNICALL Java_io_github_neva1ack_toml_TOMLTimestamp_getDay(
    JNIEnv *env, jobject timestamp) {
    toml_timestamp_t *timestamp_ptr =
        (toml_timestamp_t *)toml_handle_to_ptr(env, timestamp);
    if (!timestamp_ptr || !timestamp_ptr->day)
        goto error;
    return *timestamp_ptr->day;
error:
    return 0;
}

JNIEXPORT jint JNICALL Java_io_github_neva1ack_toml_TOMLTimestamp_getHour(
    JNIEnv *env, jobject timestamp) {
    toml_timestamp_t *timestamp_ptr =
        (toml_timestamp_t *)toml_handle_to_ptr(env, timestamp);
    if (!timestamp_ptr || !timestamp_ptr->hour)
        goto error;
    return *timestamp_ptr->hour;
error:
    return 0;
}

JNIEXPORT jint JNICALL Java_io_github_neva1ack_toml_TOMLTimestamp_getMinute(
    JNIEnv *env, jobject timestamp) {
    toml_timestamp_t *timestamp_ptr =
        (toml_timestamp_t *)toml_handle_to_ptr(env, timestamp);
    if (!timestamp_ptr || !timestamp_ptr->minute)
        goto error;
    return *timestamp_ptr->minute;
error:
    return 0;
}

JNIEXPORT jint JNICALL Java_io_github_neva1ack_toml_TOMLTimestamp_getSecond(
    JNIEnv *env, jobject timestamp) {
    toml_timestamp_t *timestamp_ptr =
        (toml_timestamp_t *)toml_handle_to_ptr(env, timestamp);
    if (!timestamp_ptr || !timestamp_ptr->second)
        goto error;
    return *timestamp_ptr->second;
error:
    return 0;
}

JNIEXPORT jint JNICALL
Java_io_github_neva1ack_toml_TOMLTimestamp_getMilliSecond(JNIEnv *env,
                                                          jobject timestamp) {
    toml_timestamp_t *timestamp_ptr =
        (toml_timestamp_t *)toml_handle_to_ptr(env, timestamp);
    if (!timestamp_ptr || !timestamp_ptr->millisec)
        goto error;
    return *timestamp_ptr->millisec;
error:
    return 0;
}

JNIEXPORT jboolean JNICALL Java_io_github_neva1ack_toml_TOMLTimestamp_isZeroedTime(
    JNIEnv *env, jobject timestamp) {
    toml_timestamp_t *timestamp_ptr =
        (toml_timestamp_t *)toml_handle_to_ptr(env, timestamp);
    if (!timestamp_ptr || !timestamp_ptr->z)
        goto error;
    // TODO: I'm unsure what this is meant to return or what 'z' means in timestamps
    // I assume timestamp.z just means if it has a 'Z' at the end and therefore should be a boolean
    return *timestamp_ptr->z;
error:
    return 0;
}

JNIEXPORT void JNICALL Java_io_github_neva1ack_toml_TOMLTimestamp_free(
    JNIEnv *env, jobject timestamp) {
    toml_timestamp_t *timestamp_ptr =
        (toml_timestamp_t *)toml_handle_to_ptr(env, timestamp);
    free(timestamp_ptr);
}
