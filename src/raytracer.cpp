#include "raytracer.hpp"
#include "options.hpp"
#include "util/log.hpp"
#include "util/profiler.hpp"

RaytracerOptions* Options = nullptr;

void init() {
    Options = new RaytracerOptions();
    initLogging();
    if (Options->profiling)
        profiler.init();
}
