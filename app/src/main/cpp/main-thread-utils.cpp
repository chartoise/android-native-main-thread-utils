//
// Created by arex.huang on 2021/4/13.
//

#include "main-thread-utils.h"

#include <cassert>
#include <string>
#include <utility>

namespace main_thread_utils {

namespace {

const char kClassName[] = "com/chartoise/main/thread/util/MainThreadTask";
jclass g_class = nullptr;
JavaVM *g_java_vm = nullptr;

void run(JNIEnv *env, jobject thiz, std::function<void()> *task) {
    assert(env != nullptr && thiz != nullptr && task != nullptr);
    task->operator()();
    delete task;
}

}  // namespace

void JniOnLoad(JavaVM *java_vm) {
    assert(java_vm != nullptr);
    assert(g_java_vm == nullptr);

    JNIEnv *env = nullptr;
    assert(JNI_OK == java_vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_4));
    assert(env != nullptr);

    g_class = env->FindClass(kClassName);
    assert(g_class != nullptr);
    g_class = static_cast<jclass>(env->NewGlobalRef(g_class));

    JNINativeMethod native_methods[] = {{"run", "(J)V", (void *)(&run)}};
    assert(JNI_OK == env->RegisterNatives(g_class, native_methods,
                                          sizeof(native_methods) / sizeof(native_methods[0])));

    g_java_vm = java_vm;
}

void internal::Post(std::function<void()> &&task) {
    assert(g_java_vm != nullptr);
    bool attached = false;
    JNIEnv *env = nullptr;
    if (g_java_vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_4) != JNI_OK) {
        assert(JNI_OK == g_java_vm->AttachCurrentThread(&env, nullptr));
        assert(env != nullptr);
        attached = true;
    }

    jmethodID method_id = env->GetStaticMethodID(g_class, "createAndPost", "(J)V");
    assert(method_id != nullptr);

    env->CallStaticVoidMethod(g_class, method_id, new std::function<void()>(task));

    if (attached) {
        assert(JNI_OK == g_java_vm->DetachCurrentThread());
    }
}

}  // namespace main_thread_utils
