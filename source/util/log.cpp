#include "log.hpp"
#include "error.hpp"
#include <print>

LogLevel logLevel = LogLevel::Error;
FILE *logFile;

void initLogging(LogLevel level, std::string logFile, bool logUtilization) {
    logLevel = level;
    if (!logFile.empty()) {
        //logFile = FOpenWizite(logFile);
        if (!logFile)
            errorExit("%s: %s", logFile, errorString());
        logLevel = LogLevel::Verbose;
    }

    if (level == LogLevel::Invalid)
        errorExit("Invalid --log-level specified.");
}

LogLevel LogLevelFromString(const std::string &s) {
    if (s == "verbose")
        return LogLevel::Verbose;
    else if (s == "error")
        return LogLevel::Error;
    else if (s == "fatal")
        return LogLevel::Fatal;
    return LogLevel::Invalid;
}

std::string ToString(LogLevel level) {
    switch (level) {
    case LogLevel::Verbose:
        return "VERBOSE";
    case LogLevel::Error:
        return "ERROR";
    case LogLevel::Fatal:
        return "FATAL";
    default:
        return "UNKNOWN";
    }
}

