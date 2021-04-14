//
// Created by arex.huang on 2021/4/14.
//
#include "test.h"

#include <ctime>
#include <string>

#include "log.h"
#include "main-thread-utils.h"

#undef TAG
#define TAG "test.cpp"

void test1(int a, int b, const std::string& s) { LOGD("a:%d, b:%d, %s", a, b, s.c_str()); }

uint64_t currentTimeMs() {
    struct timeval time {};
    gettimeofday(&time, nullptr);
    return time.tv_sec * 1000 + time.tv_usec / 1000;
}

void test() {
    LOGD();
    uint64_t count = 1000;
    while (count-- > 0) {
        main_thread_utils::Post(
            [count] { LOGD("start in main, %llu, count:%llu", currentTimeMs(), count); });
        main_thread_utils::Post(std::bind(test1, 1, 2, std::string("TEST")));
        main_thread_utils::Post(std::bind(currentTimeMs));
    }
}
