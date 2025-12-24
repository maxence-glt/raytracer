#pragma once

#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "timing.hpp"

struct Sample {
    int index = 0;
    int parent = 0;

    size_t calls = 0;

    timePoint lastTick{};
    high_resolution_clock::duration timeAlive{};

    bool alive = false;
};

class Profiler;
extern Profiler profiler;

void sample_end(Sample* sample);

inline constexpr auto sampleDeleter = [](Sample* s) noexcept {
    if (s && s->alive) sample_end(s);
};

using SampleHandle = std::unique_ptr<Sample, decltype(sampleDeleter)>;

[[nodiscard]] SampleHandle sample_start(std::string_view sampleName);

class Profiler {
public:
    void init() {
        profiling = true;
        firstTick = curr_time();
        currIndex = 1;
        stack.clear();
        stack.reserve(20);
        stack.push_back(0);
    }

    void shutdown() { profiling = false; }
    void print();

    bool profiling = false;

private:
    friend SampleHandle sample_start(std::string_view sampleName);
    friend void sample_end(Sample* sample);

    int currIndex = 1;

    std::vector<int> stack{0};

    timePoint firstTick{};

    using Bucket = std::map<int, Sample>;
    std::map<std::string, Bucket, std::less<>> samples;
};

#define PROF_CONCAT(a, b) a##b
#define PROFILE_SCOPE(name) \
    auto PROF_CONCAT(_profile_scope_, __COUNTER__) = sample_start(name)
