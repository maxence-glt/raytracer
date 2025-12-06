#pragma once

#include <format>
#include <string>

enum class LogLevel { Verbose, Error, Fatal, Invalid };

std::string toString(LogLevel level);
LogLevel logLevelFromString(const std::string &s);

void initLogging(LogLevel level, std::string logFile, bool logUtilization);
void shutdownLogging();

namespace logging {
extern LogLevel logLevel;
extern FILE *logFile;
} // namespace logging

void log(LogLevel level, const char *file, int line, const char *s);

template <typename... Args>
inline void log(LogLevel level, const char *file, int line, const char *fmt,
                Args &&...args);

[[noreturn]] void logFatal(LogLevel level, const char *file, int line,
                           const char *s);

template <typename... Args>
[[noreturn]] inline void logFatal(LogLevel level, const char *file, int line,
                                  const char *fmt, Args &&...args);

#define LOG_VERBOSE(...)              \
    (LogLevel::Verbose >= logging::logLevel && \
     (log(LogLevel::Verbose, __FILE__, __LINE__, __VA_ARGS__), true))

#define LOG_ERROR(...)              \
    (LogLevel::Error >= logging::logLevel && \
     (log(LogLevel::Error, __FILE__, __LINE__, __VA_ARGS__), true))

#define LOG_FATAL(...) logFatal(LogLevel::Fatal, __FILE__, __LINE__, __VA_ARGS__)

template <typename... Args>
inline void log(LogLevel level, const char *file, int line, const char *fmt,
                Args &&...args) {
    std::string s = std::vformat(fmt, std::make_format_args(args...));
    log(level, file, line, s.c_str());
}

template <typename... Args>
inline void logFatal(LogLevel level, const char *file, int line, const char *fmt,
                     Args &&...args) {
    std::string s = std::vformat(fmt, std::make_format_args(args...));
    logFatal(level, file, line, s.c_str());
}
