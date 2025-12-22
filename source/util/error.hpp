#pragma once
#include <string>
#include <string_view>
#include <format>
#include <cstdio>
#include <utility>

struct FileLoc {
    FileLoc() = default;
    FileLoc(std::string_view filename, int line, int col)
        : filename(filename), line(line), column(col) {}

    std::string toString() const;

    std::string_view filename;
    int line = 1, column = 0;
};

void suppressErrorMessages();
void printStackTrace(FILE* out = stderr, unsigned int max_frames = 65);

// base (non-template) endpoints
void warning(const FileLoc* loc, const std::string& message);
void error(const FileLoc* loc, const std::string& message);
[[noreturn]] void errorFatal(const FileLoc* loc, const std::string& message);

// template helpers
template<class... Args>
inline void warning(const FileLoc* loc, std::format_string<Args...> fmt, Args&&... args) {
    warning(loc, std::format(fmt, std::forward<Args>(args)...));
}
template<class... Args>
inline void warning(std::format_string<Args...> fmt, Args&&... args) {
    warning(nullptr, fmt, std::forward<Args>(args)...);
}

template<class... Args>
inline void error(const FileLoc* loc, std::format_string<Args...> fmt, Args&&... args) {
    error(loc, std::format(fmt, std::forward<Args>(args)...));
}
template<class... Args>
inline void error(std::format_string<Args...> fmt, Args&&... args) {
    error(nullptr, fmt, std::forward<Args>(args)...);
}

template<class... Args>
[[noreturn]] inline void errorFatal(const FileLoc* loc, std::format_string<Args...> fmt, Args&&... args) {
    errorFatal(loc, std::format(fmt, std::forward<Args>(args)...));
}
template<class... Args>
[[noreturn]] inline void errorFatal(std::format_string<Args...> fmt, Args&&... args) {
    errorFatal(nullptr, fmt, std::forward<Args>(args)...);
}

int lastError();
std::string errorString(int errorId = lastError());
void testErrors();
