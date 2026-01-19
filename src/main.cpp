#include "render/render.hpp"
#include "worlds/worlds.hpp"
#include "util/log.hpp"
#include "util/profiler.hpp"

int main() {
    initLogging();
    profiler.init();
    LOG_VERBOSE("Starting raytracing:");

    auto s = sample_start("main");

    auto scene = manyBalls();
    render(scene);

    sample_end(s.release());
    profiler.print(true);
    LOG_VERBOSE("Finished render succesfully, shutting down logging\n\n******************************************************\n\n");

    return 0;
}
