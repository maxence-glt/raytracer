#include <string>
#include <format>

struct FileLoc {
    FileLoc() = default;
    FileLoc(std::string_view filename, int line, int col) 
    : filename(filename), line(line), column(col) {}
    std::string toString() const;

    std::string_view filename;
    int line = 1, column = 0;
};


void suppressErrorMessages();

// declarations
void warning(const FileLoc *loc, const char *message);
void error(const FileLoc *loc, const char *message);
[[noreturn]] void errorExit(const FileLoc *loc, const char *message);

template <typename... Args>
inline void warning(const char *fmt, Args &&...args);
template <typename... Args>
inline void error(const char *fmt, Args &&...args);
template <typename... Args>
[[noreturn]] inline void errorExit(const char *fmt, Args &&...args);

// definitions
template <typename... Args>
inline void warning(const FileLoc *loc, const char *fmt, Args &&...args) {
    warning(loc, std::vformat(fmt, std::make_format_args(args...)).c_str());
}

template <typename... Args>
inline void warning(const char *fmt, Args &&...args) {
    warning(nullptr, std::vformat(fmt, std::make_format_args(args...)).c_str());
}

template <typename... Args>
inline void error(const char *fmt, Args &&...args) {
    error(nullptr, std::vformat(fmt, std::make_format_args(args...)).c_str());
}

template <typename... Args>
inline void error(const FileLoc *loc, const char *fmt, Args &&...args) {
    error(loc, std::vformat(fmt, std::make_format_args(args...)).c_str());
}

template <typename... Args>
[[noreturn]] inline void errorExit(const char *fmt, Args &&...args) {
    errorExit(nullptr, std::vformat(fmt, std::make_format_args(args...)).c_str());
}

template <typename... Args>
[[noreturn]] inline void errorExit(const FileLoc *loc, const char *fmt, Args &&...args) {
    errorExit(loc, std::vformat(fmt, std::make_format_args(args...)).c_str());
}

int lastError();
std::string errorString(int errorId = lastError());
