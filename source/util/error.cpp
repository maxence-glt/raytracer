#include <print>
#include <format>

#include "error.hpp"
#include "log.hpp"

static bool quiet = false;

void suppressErrorMessages() {
    quiet = true;
}

std::string FileLoc::toString() const {
    return std::format("{}:{}:{}", std::string(filename.data(), filename.size()), line,
                        column);
}

// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
inline std::string red(const std::string &s) {
    const std::string red = "\033[1m\033[31m";
    const std::string reset = "\033[0m";
    return red + s + reset;
}

static void processError(const char *errorType, const FileLoc *loc, const char *message) {
    // Build up an entire formatted error string and print it all at once;
    // this way, if multiple threads are printing messages at once, they
    // don't get jumbled up...
    std::string errorString;

    if (loc)
        errorString += ": " + loc->toString();

    errorString += ": ";
    errorString += message;

    // Print the error message (but not more than one time).
    static std::string lastError;
    if (errorString != lastError) {
        std::print(stderr, "{}\n", red(errorType) + errorString);
        LOG_VERBOSE("{}", errorType + errorString);
        lastError = errorString;
    }
}

void warning(const FileLoc *loc, const char *message) {
    if (quiet)
        return;
    processError("Warning", loc, message);
}

void error(const FileLoc *loc, const char *message) {
    if (quiet)
        return;
    processError("Error", loc, message);
}

void errorExit(const FileLoc *loc, const char *message) {
    processError("Fatal Error", loc, message);
    exit(1);
}

int lastError() {
    return errno;
}

std::string errorString(int errorId) {
    return std::format("{} ({})", strerror(errorId), errorId);
}

void testErrors() {
    warning("warning (no loc): {} {}", "test", 1);

    FileLoc wloc(__FILE__, __LINE__, 10);
    warning(&wloc, "warning (with loc): file='{}' line={} col={}",
            wloc.filename, wloc.line, wloc.column);

    error("error (no loc): {} {}", "test", 2);

    FileLoc eloc(__FILE__, __LINE__, 20);
    error(&eloc, "error (with loc): file='{}' line={} col={}",
          eloc.filename, eloc.line, eloc.column);

    //errorExit("fatal error (no loc): {} {}", "test", 3);

    /*
    errorExit(&eloc,
              "fatal error (with loc): file='{}' line={} col={}", eloc.filename, eloc.line, eloc.column);
    */
}
