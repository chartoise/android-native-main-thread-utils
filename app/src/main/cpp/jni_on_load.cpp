#include <jni.h>

#include <string>

#include "log.h"
#include "main-thread-utils.h"
#include "test.h"

#undef TAG
#define TAG "jni_on_load.cpp"

extern "C" jint JNI_OnLoad(JavaVM* vm, void*) {
    LOGD();
    JNIEnv* env = nullptr;
    if (JNI_OK != vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_4)) {
        return JNI_ERR;
    }

    main_thread_utils::JniOnLoad(vm);

    return JNI_VERSION_1_4;
}

extern "C" void Java_com_chartoise_main_thread_util_MainActivity_runTests(JNIEnv* env,
                                                                          jobject thiz) {
    LOGD();
    test();
}