#pragma once

#include "util/log.hpp"
#include <thread>

struct RaytracerOptions {
    unsigned int seed = 0xDEADBEEF;
    int nThreads = std::thread::hardware_concurrency();
    LogLevel logLevel = LogLevel::Verbose;
    std::string logFile = "";
    bool profiling = false;
};

extern RaytracerOptions *Options;
