#include <io_github_neva1ack_toml_TOMLTable.h>
#include <toml.h>
#include <toml_jni_common.h>

#include <stdio.h>
#include <stdlib.h>

JNIEXPORT jobject JNICALL Java_io_github_neva1ack_toml_TOMLTable_parseFile(
    JNIEnv *env, jclass table_class, jstring filename) {
    // TODO: JNI spec is slgihtly unclear on whether is is null terminated
    const char *filename_cstr = (*env)->GetStringUTFChars(env, filename, NULL);
    if (!filename_cstr)
        goto error;
    FILE *fp = fopen(filename_cstr, "r");
    (*env)->ReleaseStringUTFChars(env, filename, filename_cstr);
    if (!fp)
        goto error;
    char errbuf[200];
    toml_table_t *table = toml_parse_file(fp, errbuf, sizeof(errbuf));
    fclose(fp);
    if (!table)
        goto error;
    jmethodID TOMTable_init =
        (*env)->GetMethodID(env, table_class, "<init>", "(J)V");
    return (*env)->NewObject(env, table_class, TOMTable_init, (jlong)table);
error:
    return NULL;
}

JNIEXPORT jobject JNICALL Java_io_github_neva1ack_toml_TOMLTable_parse(
    JNIEnv *env, jclass table_class, jstring conf) {
    // TODO: JNI spec is slgihtly unclear on whether is is null terminated
    char *conf_cstr = (*env)->GetStringUTFChars(env, conf, NULL);
    if (!conf_cstr)
        goto error;
    char errbuf[200];
    toml_table_t *table = toml_parse(conf_cstr, errbuf, sizeof(errbuf));
    (*env)->ReleaseStringUTFChars(env, conf, conf_cstr);
    if (!table)
        goto error;
    jmethodID TOMLTable_constructor =
        (*env)->GetMethodID(env, table_class, "<init>", "(J)V");
    return (*env)->NewObject(env, table_class, TOMLTable_constructor,
                             (jlong)table);
error:
    return NULL;
}

JNIEXPORT void JNICALL
Java_io_github_neva1ack_toml_TOMLTable_free(JNIEnv *env, jobject table) {
    toml_table_t *table_ptr = (toml_table_t *)toml_handle_to_ptr(env, table);
    if (!table_ptr)
        goto error;
    toml_free(table_ptr);
error:
    return;
}

JNIEXPORT jstring JNICALL Java_io_github_neva1ack_toml_TOMLTable_getKeyIn(
    JNIEnv *env, jobject table, jint idx) {
    toml_table_t *table_ptr = (toml_table_t *)toml_handle_to_ptr(env, table);
    if (!table_ptr)
        goto error;
    const char *key_cstr = toml_key_in(table_ptr, idx);
    if (!key_cstr)
        goto error;
    return (*env)->NewStringUTF(env, key_cstr);
error:
    return NULL;
}

JNIEXPORT jboolean JNICALL Java_io_github_neva1ack_toml_TOMLTable_isKeyExists(
    JNIEnv *env, jobject table, jstring key) {
    toml_table_t *table_ptr = (toml_table_t *)toml_handle_to_ptr(env, table);
    if (!table_ptr)
        goto error;
    // TODO: JNI spec is unclearly whether this is null terminated
    const char *key_cstr = (*env)->GetStringUTFChars(env, key, NULL);
    if (!key_cstr)
        goto error;
    int exists = toml_key_exists(table_ptr, key_cstr);
    (*env)->ReleaseStringUTFChars(env, key, key_cstr);
    return exists;
error:
    return 0;
}

JNIEXPORT jstring JNICALL Java_io_github_neva1ack_toml_TOMLTable_getStringIn(
    JNIEnv *env, jobject table, jstring key) {
    toml_table_t *table_ptr = (toml_table_t *)toml_handle_to_ptr(env, table);
    if (!table_ptr)
        goto error;
    // TODO: JNI spec is unclearly whether this is null terminated
    const char *key_cstr = (*env)->GetStringUTFChars(env, key, NULL);
    if (!key_cstr)
        goto error;
    toml_datum_t datum = toml_string_in(table_ptr, key_cstr);
    (*env)->ReleaseStringUTFChars(env, key, key_cstr);
    if (!datum.ok)
        goto error;
    // TODO: this has to be freed at some point
    // possibly with a try-with-resources?
    char *cstr = datum.u.s;
    jstring ret = (*env)->NewStringUTF(env, cstr);
    free(cstr);
    return ret;
error:
    return NULL;
}

JNIEXPORT jboolean JNICALL Java_io_github_neva1ack_toml_TOMLTable_getBooleanIn(
    JNIEnv *env, jobject table, jstring key) {
    toml_table_t *table_ptr = (toml_table_t *)toml_handle_to_ptr(env, table);
    if (!table_ptr)
        goto error;
    // TODO: JNI spec is unclearly whether this is null terminated
    const char *key_cstr = (*env)->GetStringUTFChars(env, key, NULL);
    if (!key_cstr)
        goto error;
    toml_datum_t datum = toml_bool_in(table_ptr, key_cstr);
    (*env)->ReleaseStringUTFChars(env, key, key_cstr);
    if (!datum.ok)
        goto error;
    return datum.u.b;
error:
    return 0;
}

JNIEXPORT jlong JNICALL Java_io_github_neva1ack_toml_TOMLTable_getIntIn(
    JNIEnv *env, jobject table, jstring key) {
    toml_table_t *table_ptr = (toml_table_t *)toml_handle_to_ptr(env, table);
    if (!table_ptr)
        goto error;
    // TODO: JNI spec is unclearly whether this is null terminated
    const char *key_cstr = (*env)->GetStringUTFChars(env, key, NULL);
    if (!key_cstr)
        goto error;
    toml_datum_t datum = toml_int_in(table_ptr, key_cstr);
    (*env)->ReleaseStringUTFChars(env, key, key_cstr);
    if (!datum.ok)
        goto error;
    return datum.u.i;
error:
    return 0;
}

JNIEXPORT jdouble JNICALL Java_io_github_neva1ack_toml_TOMLTable_getDoubleIn(
    JNIEnv *env, jobject table, jstring key) {
    toml_table_t *table_ptr = (toml_table_t *)toml_handle_to_ptr(env, table);
    if (!table_ptr)
        goto error;
    // TODO: JNI spec is unclearly whether this is null terminated
    const char *key_cstr = (*env)->GetStringUTFChars(env, key, NULL);
    if (!key_cstr)
        goto error;
    toml_datum_t datum = toml_double_in(table_ptr, key_cstr);
    (*env)->ReleaseStringUTFChars(env, key, key_cstr);
    if (!datum.ok)
        goto error;
    return datum.u.d;
error:
    return 0;
}

JNIEXPORT jobject JNICALL Java_io_github_neva1ack_toml_TOMLTable_getTimestampIn(
    JNIEnv *env, jobject table, jstring key) {
    toml_table_t *table_ptr = (toml_table_t *)toml_handle_to_ptr(env, table);
    if (!table_ptr)
        goto error;
    // TODO: JNI spec is unclearly whether this is null terminated
    const char *key_cstr = (*env)->GetStringUTFChars(env, key, NULL);
    if (!key_cstr)
        goto error;
    toml_datum_t datum = toml_timestamp_in(table_ptr, key_cstr);
    (*env)->ReleaseStringUTFChars(env, key, key_cstr);
    if (!datum.ok)
        goto error;
    // this is freed with a try-with-resources
    toml_timestamp_t *timestamp = datum.u.ts;
    jclass TOMLTimestamp =
        (*env)->FindClass(env, "io/github/neva1ack/toml/TOMLTimestamp");
    jmethodID TOMLTimestamp_constructor =
        (*env)->GetMethodID(env, TOMLTimestamp, "<init>", "(J)V");
    return (*env)->NewObject(env, TOMLTimestamp, TOMLTimestamp_constructor,
                             (jlong)timestamp);
error:
    return NULL;
}

JNIEXPORT jobject JNICALL Java_io_github_neva1ack_toml_TOMLTable_getArrayIn(
    JNIEnv *env, jobject table, jstring key) {
    toml_table_t *table_ptr = (toml_table_t *)toml_handle_to_ptr(env, table);
    if (!table_ptr)
        goto error;
    // TODO: JNI spec is unclearly whether this is null terminated
    const char *key_cstr = (*env)->GetStringUTFChars(env, key, NULL);
    if (!key_cstr)
        goto error;
    toml_array_t *array = toml_array_in(table_ptr, key_cstr);
    (*env)->ReleaseStringUTFChars(env, key, key_cstr);
    if (!array)
        goto error;
    jclass TOMLArray =
        (*env)->FindClass(env, "io/github/neva1ack/toml/TOMLArray");
    jmethodID TOMLArray_constructor =
        (*env)->GetMethodID(env, TOMLArray, "<init>", "(J)V");
    return (*env)->NewObject(env, TOMLArray, TOMLArray_constructor,
                             (jlong)array);
error:
    return NULL;
}

JNIEXPORT jobject JNICALL Java_io_github_neva1ack_toml_TOMLTable_getTableIn(
    JNIEnv *env, jobject table, jstring key) {
    toml_table_t *table_ptr = (toml_table_t *)toml_handle_to_ptr(env, table);
    if (!table_ptr)
        goto error;
    // TODO: JNI spec is unclearly whether this is null terminated
    const char *key_cstr = (*env)->GetStringUTFChars(env, key, NULL);
    if (!key_cstr)
        goto error;
    toml_table_t *table_in = toml_table_in(table_ptr, key_cstr);

    (*env)->ReleaseStringUTFChars(env, key, key_cstr);
    if (!table_in)
        goto error;
    jclass TOMLTable = (*env)->GetObjectClass(env, table);
    jmethodID TOMLTable_constructor =
        (*env)->GetMethodID(env, TOMLTable, "<init>", "(J)V");
    return (*env)->NewObject(env, TOMLTable, TOMLTable_constructor,
                             (jlong)table_in);
error:
    return NULL;
}
