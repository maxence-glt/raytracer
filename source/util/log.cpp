#include "log.hpp"
#include "error.hpp"
#include "timing.hpp"
#include <cstdio>
#include <exception>
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
        if (!logging::logFile) {
            std::print("{}: {}", logFile, errorString());
            std::terminate();
        }
        logging::logLevel = LogLevel::Verbose;
    }

    if (level == LogLevel::Invalid) {
        std::print("Invalid --log-level specified.");
        std::terminate();
    }

    if (logUtilization) {
        // TODO: https://stackoverflow.com/a/1911863/21144460
        // make logging its own thread
    }
}

// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
inline std::string red(const std::string &s) {
    const std::string red = "\033[1m\033[31m";
    const std::string reset = "\033[0m";
    return red + s + reset;
}

inline std::string yellow(const std::string &s) {
    const std::string yellow = "\033[1m\033[33m";
    const std::string reset = "\033[0m";
    return yellow + s + reset;
}

inline std::string green(const std::string &s) {
    const std::string green = "\033[1m\033[32m";
    const std::string reset = "\033[0m";
    return std::string(green) + s + std::string(reset);
}

std::string toString(LogLevel level, bool colored) {
    switch (level) {
        case LogLevel::Verbose:
            return "";
        case LogLevel::Warning:
            return colored ? yellow("WARNING") : "WARNING";
        case LogLevel::Error:
            return colored ? red("ERROR") : "ERROR";
        case LogLevel::Debug:
            return colored ? green("DEBUG") : "DEBUG";
        case LogLevel::Fatal:
            return colored ? red("FATAL") : "FATAL";
        default:
            return "UNKNOWN";
    }
}

void log(LogLevel level, const char *file, int line, const std::string &s) {
    if (s.empty())
        return;

    std::println(stderr,
        "[ {} {}:{} ] {}{}",
        elapsedSeconds(),
        file, line,
        toString(level, true) + (level == LogLevel::Verbose ? "" : " "),
        s
    );
    std::fflush(stderr);

    if (logging::logFile) {
        std::println(logging::logFile,
            "[ {} {}:{} ] {}{}",
            elapsedSeconds(),
            file, line,
            toString(level, false) + (level == LogLevel::Verbose ? "" : " "),
            s
        );
        std::fflush(logging::logFile);
    }
}

void testLogs() {
    LOG_VERBOSE("testing log verbose");
    LOG_DEBUG("testing log debug");
    LOG_WARNING("testing log warning");
    LOG_ERROR("testing log error");
    LOG_FATAL("testing log fatal");
}
