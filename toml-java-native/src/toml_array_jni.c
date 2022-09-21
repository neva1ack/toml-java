#include <io_github_neva1ack_toml_TOMLArray.h>
#include <stdlib.h>
#include <toml.h>
#include <toml_jni_common.h>

JNIEXPORT jint JNICALL
Java_io_github_neva1ack_toml_TOMLArray_getSize(JNIEnv *env, jobject array) {
    toml_array_t *array_ptr = (toml_array_t *)toml_handle_to_ptr(env, array);
    if (!array_ptr)
        goto error;
    int size = toml_array_nelem(array_ptr);
    return size;
error:
    return 0;
}

JNIEXPORT jstring JNICALL Java_io_github_neva1ack_toml_TOMLArray_getStringAt(
    JNIEnv *env, jobject array, jint idx) {
    toml_array_t *array_ptr = (toml_array_t *)toml_handle_to_ptr(env, array);
    if (!array_ptr)
        goto error;
    toml_datum_t datum = toml_string_at(array_ptr, idx);
    if (!datum.ok)
        goto error;
    char *cstr = datum.u.s;
    jstring ret = (*env)->NewStringUTF(env, cstr);
    free(cstr);
    return ret;
error:
    return 0;
}

JNIEXPORT jboolean JNICALL Java_io_github_neva1ack_toml_TOMLArray_getBooleanAt(
    JNIEnv *env, jobject array, jint idx) {
    toml_array_t *array_ptr = (toml_array_t *)toml_handle_to_ptr(env, array);
    if (!array_ptr)
        goto error;
    toml_datum_t datum = toml_bool_at(array_ptr, idx);
    if (!datum.ok)
        goto error;
    return datum.u.b;
error:
    return 0;
}

JNIEXPORT jlong JNICALL Java_io_github_neva1ack_toml_TOMLArray_getIntAt(
    JNIEnv *env, jobject array, jint idx) {
    toml_array_t *array_ptr = (toml_array_t *)toml_handle_to_ptr(env, array);
    if (!array_ptr)
        goto error;
    toml_datum_t datum = toml_int_at(array_ptr, idx);
    if (!datum.ok)
        goto error;
    return datum.u.i;
error:
    return 0;
}

JNIEXPORT jdouble JNICALL Java_io_github_neva1ack_toml_TOMLArray_getDoubleAt(
    JNIEnv *env, jobject array, jint idx) {
    toml_array_t *array_ptr = (toml_array_t *)toml_handle_to_ptr(env, array);
    if (!array_ptr)
        goto error;
    toml_datum_t datum = toml_double_at(array_ptr, idx);
    if (!datum.ok)
        goto error;
    return datum.u.d;
error:
    return 0;
}

JNIEXPORT jobject JNICALL Java_io_github_neva1ack_toml_TOMLArray_getTimestampAt(
    JNIEnv *env, jobject array, jint idx) {
    toml_array_t *array_ptr = (toml_array_t *)toml_handle_to_ptr(env, array);
    if (!array_ptr)
        goto error;
    toml_datum_t datum = toml_timestamp_at(array_ptr, idx);
    if (!datum.ok)
        goto error;
    // this is freed with a try-with-resources
    toml_timestamp_t *timestamp = datum.u.ts;
    jclass TOMLTimestamp =
        (*env)->FindClass(env, "io/github/neva1ack/toml/TOMLTimestamp");
    jmethodID TOMLTimestamp_constructor = (*env)->GetMethodID(
        env, TOMLTimestamp, "<init>", "(J)V");
    return (*env)->NewObject(env, TOMLTimestamp, TOMLTimestamp_constructor,
                             (jlong)timestamp);
error:
    return NULL;
}

JNIEXPORT jobject JNICALL Java_io_github_neva1ack_toml_TOMLArray_getArrayAt(
    JNIEnv *env, jobject array, jint idx) {
    toml_array_t *array_ptr = (toml_array_t *)toml_handle_to_ptr(env, array);
    if (!array_ptr)
        goto error;
    toml_array_t *array_in = toml_array_at(array_ptr, idx);
    if (!array_in)
        goto error;
    jclass TOMLArray = (*env)->GetObjectClass(env, array);
    jmethodID TOMLArray_constructor = (*env)->GetMethodID(env, TOMLArray, "<init>", "(J)V");
    return (*env)->NewObject(env, TOMLArray, TOMLArray_constructor, (jlong)array_in);
error:
    return NULL;
}

JNIEXPORT jobject JNICALL Java_io_github_neva1ack_toml_TOMLArray_getTableAt(
    JNIEnv *env, jobject array, jint idx) {
    toml_array_t *array_ptr = (toml_array_t *)toml_handle_to_ptr(env, array);
    if (!array_ptr)
        goto error;
    toml_table_t *table_in = toml_table_at(array_ptr, idx);
    if (!table_in)
        goto error;
    jclass TOMLTable = (*env)->FindClass(env, "io/github/neva1ack/toml/TOMLTable");
    jmethodID TOMLTable_constructor = (*env)->GetMethodID(env, TOMLTable, "<init>", "(J)V");
    return (*env)->NewObject(env, TOMLTable, TOMLTable_constructor, (jlong) table_in);
error:
    return NULL;
}
