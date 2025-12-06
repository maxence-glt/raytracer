#pragma once

#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;

using std::chrono::nanoseconds;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::milliseconds;

using timePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

// current time
inline timePoint curr_time() {
    return high_resolution_clock::now();
}

template <typename T>
inline T diff_time(timePoint t1, timePoint t2) {
    return duration_cast<T>(t2 - t1);
}
