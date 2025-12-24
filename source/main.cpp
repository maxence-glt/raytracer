#include "integrations.hpp"
#include "util/timing.hpp"
#include "worlds.hpp"
#include "util/vecmath.hpp"
#include "util/error.hpp"
#include "util/log.hpp"
#include "util/math.hpp"
#include "util/vecmath.hpp"
#include "util/profiler.hpp"
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <cxxabi.h>
#include <thread>
#include <vector>
#include "util/check.h"

Profiler profiler;

int main() {
    initLogging();
    LOG_VERBOSE("Starting raytracing:");
    profiler.init();

    auto s = sample_start("main");

    many_balls();
    //testErrors();
    //testLogs();

    sample_end(s.release());

    profiler.print();

    LOG_VERBOSE("Finished render succesfully, shutting down logging\n\n******************************************************\n\n");

    return 0;
}
