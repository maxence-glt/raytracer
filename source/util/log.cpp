#include "log.hpp"
#include "error.hpp"
#include "timing.hpp"
#include <cstdio>
#include <print>

float elapsedSeconds() {
    using clock = std::chrono::steady_clock;
    static timePoint start = curr_time();

    timePoint now = clock::now();
    int64_t elapseduS = diff_time<milliseconds>(start, now).count();
    return elapseduS / 1e3;
}

namespace logging {
LogLevel logLevel = LogLevel::Error;
FILE *logFile;
} // namespace logging

void initLogging(LogLevel level, std::string logFile, bool logUtilization) {
    logging::logLevel = level;
    if (!logFile.empty()) {
        logFile = "../logs/" + logFile + ".log";
        logging::logFile = fopen(logFile.c_str(), "ab");
        if (!logging::logFile)
            errorExit("{}: {}", logFile, errorString());
        logging::logLevel = LogLevel::Verbose;
    }

    if (level == LogLevel::Invalid)
        errorExit("Invalid --log-level specified.");

    if (logUtilization) {
        // TODO: https://stackoverflow.com/a/1911863/21144460
        // make logging its own thread
    }
}

LogLevel logLevelFromString(const std::string &s) {
    if (s == "verbose")
        return LogLevel::Verbose;
    else if (s == "error")
        return LogLevel::Error;
    else if (s == "fatal")
        return LogLevel::Fatal;
    return LogLevel::Invalid;
}

std::string toString(LogLevel level) {
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

void log(LogLevel level, const char *file, int line, const char *s) {
    if (!s || s[0] == '\0')
        return;

    std::string levelString;
    if (level != LogLevel::Verbose) {
        levelString = toString(level);
        levelString.push_back(' ');
    }

    std::FILE* out = logging::logFile ? logging::logFile : stderr;

    std::println(out,
        "[ {} {}:{} ] {}{}",
        elapsedSeconds(),
        file, line,
        levelString, s
    );

    if (logging::logFile) {
        std::fflush(out); // keep your old behavior
    }
}
void logFatal(LogLevel level, const char *file, int line, const char *s) {
    log(level, file, line, s);

    abort();
}
