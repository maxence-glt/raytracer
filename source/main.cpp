#include "util/error.hpp"
#include "worlds.hpp"
#include "util/log.hpp"
#include "util/profiler.hpp"

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

    profiler.print(true);

    LOG_VERBOSE("Finished render succesfully, shutting down logging\n\n******************************************************\n\n");

    return 0;
}
