#pragma once

#include <string>

enum class LogLevel { Verbose, Error, Fatal, Invalid };

std::string toString(LogLevel level);
LogLevel logLevelFromString(const std::string &s);

void initLogging(LogLevel level, std::string logFile, bool logUtilization);
void shutdownLogging();

extern LogLevel logLevel;
extern FILE *logFile;

void Log(LogLevel level, const char *file, int line, const char *s);

template <typename... Args>
inline void Log(LogLevel level, const char *file, int line, const char *fmt,
                Args &&...args);

[[noreturn]] void LogFatal(LogLevel level, const char *file, int line,
                           const char *s);

template <typename... Args>
[[noreturn]] inline void LogFatal(LogLevel level, const char *file, int line,
                                  const char *fmt, Args &&...args);

#define LOG_VERBOSE(...)              \
    (LogLevel::Verbose >= logLevel && \
     (Log(LogLevel::Verbose, __FILE__, __LINE__, __VA_ARGS__), true))

#define LOG_ERROR(...)              \
    (LogLevel::Error >= logLevel && \
     (Log(LogLevel::Error, __FILE__, __LINE__, __VA_ARGS__), true))

#define LOG_FATAL(...) LogFatal(LogLevel::Fatal, __FILE__, __LINE__, __VA_ARGS__)
