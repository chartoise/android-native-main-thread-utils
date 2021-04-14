//
// Created by arex.huang on 2021/4/14.
//

#ifndef NATIVE_MAIN_THREAD_UTIL_LOG_H
#define NATIVE_MAIN_THREAD_UTIL_LOG_H

#include <android/log.h>

#ifndef TAG
#define TAG ""
#endif

#define LOGD(fmt, ...)                                                                  \
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "(%s:%d) " fmt, __FUNCTION__, __LINE__, \
                        ##__VA_ARGS__)

#endif  // NATIVE_MAIN_THREAD_UTIL_LOG_H
