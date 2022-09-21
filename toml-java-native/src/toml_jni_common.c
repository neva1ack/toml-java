#include <toml_jni_common.h>

jlong toml_handle_to_ptr(JNIEnv *env, jobject object) {
    jclass clazz = (*env)->GetObjectClass(env, object);
    jfieldID handle_field = (*env)->GetFieldID(env, clazz, "handle", "J");
    jlong handle = (*env)->GetLongField(env, object, handle_field);
    return handle;
}
