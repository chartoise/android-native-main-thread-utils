//
// Created by arex.huang on 2021/4/13.
//

#ifndef NATIVE_MAIN_THREAD_UTIL_MAIN_THREAD_UTILS_H
#define NATIVE_MAIN_THREAD_UTIL_MAIN_THREAD_UTILS_H

#include <jni.h>

#include <functional>

namespace main_thread_utils {

namespace internal {

void Post(std::function<void()> &&task);

}  // namespace internal

void JniOnLoad(JavaVM *java_vm);

template <typename TASK>
void Post(TASK &&task) {
    internal::Post([=] { task.operator()(); });
}

}  // namespace main_thread_utils

#endif  // NATIVE_MAIN_THREAD_UTIL_MAIN_THREAD_UTILS_H
