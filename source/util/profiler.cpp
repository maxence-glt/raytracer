#include <algorithm>
#include <chrono>
#include <functional>
#include <print>
#include "profiler.hpp"
#include "timing.hpp"
#include "check.h"
#include "log.hpp"

// TODO: replace map with unordered_map when Apple Clang stops crashing
//       sample_start should take a string_view, only possible if above is fixed

SampleHandle sample_start(const std::string &sampleName) {
    if (!profiler.profiling) return nullptr;

    CHECK(sampleName.size());
    SampleHandle sample = nullptr;

    for (auto &s : profiler.samples[sampleName]) {
        if (s.callStack == profiler.callStack) {
            // if sample exists it shouldn't be alive
            DCHECK(!s.alive);
            sample.reset(&s);
        }
    }

    if (!sample) {
        profiler.samples[sampleName].emplace_back(sampleName, profiler.callStack, 
                                                  profiler.currIndex++, 0, 
                                                  timePoint{}, high_resolution_clock::duration{},
                                                  true);
        sample.reset(&profiler.samples[sampleName].back());
    }

    profiler.callStack += " ";
    profiler.callStack += std::to_string(sample->index);
    sample->alive = true;
    sample->lastTick = curr_time();

    return sample;
}

void sample_end(Sample *sample) {
    if (!profiler.profiling) return;
    CHECK(sample);
    CHECK(sample->alive);

    sample->alive = false;
    ++sample->calls;
    sample->timeAlive += curr_time() - sample->lastTick;

    auto pos = profiler.callStack.rfind(' ');
    DCHECK_NE(pos, std::string::npos);
    profiler.callStack.erase(pos);
}


static int parent_from_callstack(std::string_view cs) {
    if (cs.empty()) return 0;

    auto pos = cs.rfind(' ');
    std::string_view last = (pos == std::string_view::npos) ? cs : cs.substr(pos + 1);

    return std::stoi(std::string(last));
}

void Profiler::print() {
    if (!profiler.profiling) {
        LOG_WARNING("Ignoring Profiler::print(), profiler deactivated");
        return;
    }
    auto totalDur = (curr_time() - firstTick);

    struct Entry {
        std::string_view name;
        const Sample* s;
        int parent;
    };

    std::vector<Entry> entries;
    std::map<int, std::size_t> byIndex;
    std::map<int, std::vector<int>> children;

    for (const auto& [k, v] : samples) {
        for (const auto& s : v) {
            CHECK(s.callStack.size());
            int parent = parent_from_callstack(s.callStack);
            byIndex[s.index] = entries.size();
            entries.push_back(Entry{ k, &s, parent });
            children[parent].push_back(s.index);
        }
    }

    for (auto& [p, kids] : children) {
        std::sort(kids.begin(), kids.end(), [&](int a, int b) {
            return a < b;
        });
    }


    int nameWidth = 15;

    auto name_with_indent = [](std::string_view name, int depth) {
        return std::string(depth * 2, ' ') + std::string(name);
    };

    std::function<void(int,int)> compute_width = [&](int parentIdx, int depth) {
        auto it = children.find(parentIdx);
        if (it == children.end()) return;

        for (int childIdx : it->second) {
            auto eIt = byIndex.find(childIdx);
            if (eIt == byIndex.end()) continue;
            const Entry& e = entries[eIt->second];

            nameWidth = std::max<int>(nameWidth, depth * 2 + (int)e.name.size());
            compute_width(childIdx, depth + 1);
        }
    };

    compute_width(0, 0);

    auto print_node = [&](const Entry& e, int depth) {
        if (e.s->alive)
            LOG_WARNING("{} is marked as alive", e.s->sampleName);

        double aliveSec = std::chrono::duration<double>(e.s->timeAlive).count();
        double totalSec = std::chrono::duration<double>(totalDur).count();
        double proportion = (totalSec > 0.0) ? (aliveSec / totalSec) : 0.0;

        std::string n = name_with_indent(e.name, depth);

        std::print(stderr, "{:<{}} {:>20} {:>14.3f} {:>12.2f}%\n",
                   n, nameWidth,
                   e.s->calls,
                   aliveSec,
                   proportion * 100.0);
    };

    std::function<void(int,int)> dfs = [&](int parentIdx, int depth) {
        auto it = children.find(parentIdx);
        if (it == children.end()) return;

        for (int childIdx : it->second) {
            auto eIt = byIndex.find(childIdx);
            if (eIt == byIndex.end()) continue;
            const Entry& e = entries[eIt->second];

            print_node(e, depth);
            dfs(childIdx, depth + 1);
        }
    };

    auto title = std::format("{:<{}} {:>20} {:>14} {:>12}",
               "name", nameWidth, "calls", "sec", "prop");
    auto divider = std::string(title.size() + 2, '-');

    std::print(stderr, "\n{}\n", divider);
    std::print(stderr, "{}\n", title);
    std::print(stderr, "{}\n", divider);
    dfs(0, 0);
    std::print(stderr, "{}\n\n", divider);
}
