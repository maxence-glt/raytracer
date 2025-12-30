// profiler.cpp
#include <algorithm>
#include <chrono>
#include <format>
#include <functional>
#include <print>

#include "profiler.hpp"
#include "check.h"
#include "log.hpp"
#include "timing.hpp"

SampleHandle sample_start(std::string_view sampleName) {
    if (!profiler.profiling) return nullptr;
    DCHECK(!sampleName.empty());
    DCHECK(!profiler.stack.empty());

    const int parentId = profiler.stack.back();

    auto it = profiler.samples.find(sampleName);
    if (it == profiler.samples.end())
        it = profiler.samples.try_emplace(std::string(sampleName), Profiler::Bucket{}).first;

    auto &bucket = it->second;

    auto [sit, inserted] = bucket.try_emplace(parentId, Sample{});
    Sample &s = sit->second;

    if (inserted) {
        s.index = profiler.currIndex++;
        s.parent = parentId;
    } else {
        DCHECK(!s.alive);
        DCHECK_EQ(s.parent, parentId);
    }

    s.alive = true;
    profiler.stack.push_back(s.index);
    s.lastTick = curr_time();

    return SampleHandle(&s, sampleDeleter);
}

void sample_end(Sample* sample) {
    if (!profiler.profiling) return;
    CHECK(sample);
    CHECK(sample->alive);
    CHECK(!profiler.stack.empty());
    DCHECK_EQ(profiler.stack.back(), sample->index);

    profiler.stack.pop_back();
    sample->alive = false;

    ++sample->calls;
    sample->timeAlive += curr_time() - sample->lastTick;
}

void Profiler::print(bool sortByTime) {
    if (!profiling) {
        LOG_WARNING("Ignoring Profiler::print(), profiler deactivated");
        return;
    }

    auto totalDur = curr_time() - firstTick;

    struct Entry {
        std::string_view name;
        const Sample *s;
        int parent;
    };

    std::vector<Entry> entries;
    std::map<int, std::size_t> byIndex;
    std::map<int, std::vector<int>> children;

    entries.reserve(1024);

    for (const auto &[name, bucket] : samples) {
        for (const auto &[parentId, s] : bucket) {
            CHECK(s.index > 0);
            byIndex[s.index] = entries.size();
            entries.push_back(Entry{name, &s, s.parent});
            children[s.parent].push_back(s.index);
        }
    }

    for (auto& [p, kids] : children) {
        if (sortByTime) {
            std::sort(kids.begin(), kids.end(),
                      [&byIndex, &entries](int a, int b) {
                      return entries.at(byIndex.at(a)).s->calls >
                      entries.at(byIndex.at(b)).s->calls;
                      });
        } else {
            std::sort(kids.begin(), kids.end());
        }
    }

    int nameWidth = 15;

    auto name_with_indent = [](std::string_view name, int depth) {
        return std::string(depth * 2, ' ') + std::string(name);
    };

    std::function<void(int, int)> compute_width = [&](int parentIdx, int depth) {
        auto it = children.find(parentIdx);
        if (it == children.end()) return;

        for (int childIdx : it->second) {
            auto eIt = byIndex.find(childIdx);
            if (eIt == byIndex.end()) continue;
            const Entry &e = entries[eIt->second];

            nameWidth = std::max<int>(nameWidth, depth * 2 + (int)e.name.size());
            compute_width(childIdx, depth + 1);
        }
    };

    compute_width(0, 0);

    auto print_node = [&](const Entry& e, int depth) {
        auto dur = e.s->timeAlive;
        if (e.s->alive) dur += (curr_time() - e.s->lastTick);

        double aliveSec = std::chrono::duration<double>(dur).count();
        double totalSec = std::chrono::duration<double>(totalDur).count();
        double proportion = (totalSec > 0.0) ? (aliveSec / totalSec) : 0.0;

        std::string n = name_with_indent(e.name, depth);

        std::print(stderr, "  {:<{}} {:>9} {:>14.3f} {:>9.2f}%\n",
                   n, nameWidth + 2,
                   e.s->calls,
                   aliveSec,
                   proportion * 100.0);
    };

    std::function<void(int, int)> dfs = [&](int parentIdx, int depth) {
        auto it = children.find(parentIdx);
        if (it == children.end()) return;

        for (int childIdx : it->second) {
            auto eIt = byIndex.find(childIdx);
            if (eIt == byIndex.end()) continue;
            const Entry &e = entries[eIt->second];

            print_node(e, depth);
            dfs(childIdx, depth + 1);
        }
    };

    auto title = std::format("  {:<{}} {:>9} {:>14} {:>9}",
                             "name", nameWidth + 3, "calls", "sec", "prop");
    auto divider = std::string(title.size() + 2, '-');

    std::print(stderr, "\n{}\n", divider);
    std::print(stderr, "{}\n", title);
    std::print(stderr, "{}\n", divider);
    dfs(0, 0);
    std::print(stderr, "{}\n\n", divider);
}
