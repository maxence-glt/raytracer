#include <print>
#include <format>

#include "error.hpp"

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
    std::string errorString = red(errorType);

    if (loc)
        errorString += ": " + loc->toString();

    errorString += ": ";
    errorString += message;

    // Print the error message (but not more than one time).
    static std::string lastError;
    if (errorString != lastError) {
        std::print(stderr, "{}\n", errorString.c_str());
        //LOG_VERBOSE("%s", errorString);
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
    processError("Error", loc, message);
    exit(1);
}

int lastError() {
    return errno;
}

std::string errorString(int errorId) {
    return std::format("{} ({})", strerror(errorId), errorId);
}
