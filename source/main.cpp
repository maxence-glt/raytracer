#include "util/error.hpp"
#include "util/log.hpp"
#include "util/profiler.hpp"
#include <print>

Profiler profiler;

extern void many_balls();

int main() {
    initLogging();
    LOG_VERBOSE("Starting raytracing:");
    profiler.init();

    auto s = sample_start("main");

    many_balls();
    //testErrors();
    //testLogs();

    sample_end(s.release());

    profiler.print(true);

    LOG_VERBOSE("Finished render succesfully, shutting down logging\n\n******************************************************\n\n");

    return 0;
}
