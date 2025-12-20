#include <cstddef>
#include <memory>
#include <print>
#include <format>
#include <sstream>
#include <vector>
#include <execinfo.h>
#include <cxxabi.h>
 

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
        //TODO: replace with std::stacktrace when clang supports it
        printStackTrace(stderr, 65);
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

std::vector<std::string> splitString(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string tok;

    while (iss >> tok)
        tokens.emplace_back(tok);

    return tokens;
}

void printStackTrace(FILE *out = stderr, unsigned int max_frames = 10)
{
    std::print(out, "stack trace:\n");

    std::vector<void*> addrlist(max_frames + 1);
    size_t addrlen = backtrace(addrlist.data(), addrlist.size());

    if (addrlen == 0) {
        std::print(out, "  \n" );
        return;
    }

    // this will allocate memory
    char** temp = backtrace_symbols(addrlist.data(), addrlen);
    if (!temp) {
        std::print(out, "  <backtrace_symbols failed>\n");
        return;
    }

    std::vector<std::string> symbollist;
    symbollist.reserve(addrlen > 0 ? addrlen - 1 : 0);

    // skip printStackTrace call
    for (size_t i = 1; i < addrlen; ++i)
         symbollist.emplace_back(temp[i]);

    free(temp);

    for (const auto &it : symbollist) {
        auto prettySymbols = splitString(it);

        if (prettySymbols.size() < 6) {
            std::print(stderr, "prettySymbols.size() < 6 with it={}\n", it);
            continue;
        }

        int status = 0;
        std::unique_ptr<char, decltype(&std::free)> cxx_sname(
            abi::__cxa_demangle(prettySymbols[3].c_str(), nullptr, 0, &status),
            &std::free
        );

        if (!status && cxx_sname)
            prettySymbols[3] = cxx_sname.get();
        // ignore the errors for names that aren't mangled (errno -2)
        else if (status != -2)
            std::print(stderr, "__cxa_demangle failed with error={}\n", status);

        std::print(out, "{:3} {:15} {:25} {} {} {}\n", 
                   prettySymbols[0], prettySymbols[1], prettySymbols[2],
                   prettySymbols[3], prettySymbols[4], prettySymbols[5]);
    }

    std::print("\n");
}

