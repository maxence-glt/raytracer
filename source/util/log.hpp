#pragma once

#include "error.hpp"
#include <format>
#include <string>

enum class LogLevel {Verbose, Warning, Error, Debug, Fatal, Invalid};

std::string toString(LogLevel level, bool colored);
LogLevel logLevelFromString(const std::string &s);

void initLogging(std::string logFile = "", LogLevel level = LogLevel::Verbose);
void shutdownLogging();

namespace logging {
extern LogLevel logLevel;
extern FILE *logFile;
} // namespace logging

void log(LogLevel level, const char *file, int line, const std::string &s);

template <typename... Args>
inline void log(LogLevel level, const char *file, int line, const char *fmt,
                Args &&...args);

#define LOG_VERBOSE(...)              \
    (LogLevel::Verbose >= logging::logLevel && \
     (log(LogLevel::Verbose, __FILE__, __LINE__, __VA_ARGS__), true))

#define LOG_WARNING(...)              \
    (LogLevel::Warning >= logging::logLevel && \
     (log(LogLevel::Warning, __FILE__, __LINE__, __VA_ARGS__), true))

#define LOG_ERROR(...)              \
    (LogLevel::Error >= logging::logLevel && \
     (log(LogLevel::Error, __FILE__, __LINE__, __VA_ARGS__), true))

#define LOG_DEBUG(...)              \
    (LogLevel::Debug >= logging::logLevel && \
     (log(LogLevel::Debug, __FILE__, __LINE__, __VA_ARGS__), true))

#define LOG_FATAL(...) log(LogLevel::Fatal, __FILE__, __LINE__, __VA_ARGS__)

template <typename... Args>
inline void log(LogLevel level, const char *file, int line, const char *fmt,
                Args &&...args) {
    std::string s;
    try {
        s = std::vformat(fmt, std::make_format_args(args...));
    } catch (...) {
        errorFatal("log failed on vformat({})", fmt);
    }
    log(level, file, line, s);
}

void testLogs();
