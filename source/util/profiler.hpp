#pragma once

#include <chrono>
#include <deque>
#include <functional>
#include <memory>
#include <string>
//#include <unordered_map>
#include <map>
#include <vector>
#include "timing.hpp"

/*
* Track "samples" which are segments of code
* Profiler outputs:
*   each sample's basic info (name, location, etc)
*   avg/min/max percentage of time spent on that sample
*   # of times that sample was called
*   relationship to other samples (parent/child)
*
* Implementation:
*   To keep the call-stack in the profiler output, we 
*/

struct Sample {
    std::string sampleName;
    std::string callStack;
    int index;
    size_t calls;
    timePoint lastTick;
    high_resolution_clock::duration timeAlive;
    bool alive;
};


void sample_end(Sample *sample);

inline constexpr auto sampleDeleter = [](Sample* s) noexcept {
    if (s && s->alive) sample_end(s);
};
using SampleHandle = std::unique_ptr<Sample, decltype(sampleDeleter)>;

SampleHandle sample_start(const std::string &sampleName);

class Profiler {
public:
    void init() {
        profiling = true;
        firstTick = curr_time();
    }

    friend SampleHandle sample_start(const std::string &sampleName);
    friend void sample_end(Sample *sample);
    void print();

    bool profiling = false;

private:
    int currIndex{1};
    std::string callStack{"0"};
    timePoint firstTick;
    // change to hashmap when llvm issue is gone
    //std::unordered_map<std::string, std::vector<Sample>> samples;
    std::map<std::string, std::deque<Sample>> samples;
};

extern Profiler profiler;
