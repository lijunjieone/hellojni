#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_bn_hellojni_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

std::string jstring2string(JNIEnv *pEnv, jstring pJstring);


extern "C"
JNIEXPORT jstring JNICALL
Java_com_bn_hellojni_MainActivity_callJavaStaticMethod3(JNIEnv *env, jobject thiz, jobject context,
                                                        jstring tip) {
    jclass clazz = NULL;
    jstring str_arg = NULL;
    jstring from = NULL;
    jmethodID mid_static_method;
    // 1、从classpath路径下搜索ClassMethod这个类，并返回该类的Class对象
    clazz = env->FindClass("com/bn/hellojni/ClassMethod");
    if (clazz == NULL) {
    }

    // 2、从clazz类中查找callStaticMethod方法
    mid_static_method = env->GetStaticMethodID(clazz,"callStaticMethod","(Landroid/content/Context;Ljava/lang/String;)Ljava/lang/String;");
    if (mid_static_method == NULL) {
        printf("找不到callStaticMethod这个静态方法。");
    }

    // 3、调用clazz类的callStaticMethod静态方法
    from = (jstring)env->CallStaticObjectMethod(clazz,mid_static_method, context ,tip);

    // 删除局部引用
    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(str_arg);

    return env->NewStringUTF(jstring2string(env,from).c_str());

}


std::string jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}
