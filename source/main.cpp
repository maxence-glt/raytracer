#include "render/render.hpp"
#include "util/random.hpp"
#include "worlds/worlds.hpp"
#include "util/log.hpp"
#include "util/profiler.hpp"



int main() {
    int n = 1e7;
    float* a = (float*)std::malloc(n * sizeof(float));
    float* b = (float*)std::malloc(n * sizeof(float));
    float* c = (float*)std::malloc(n * sizeof(float));

    for (int i = 0; i < n; ++i) (a[i] = i) && (b[i] = n - i);
    for (int i = 0; i < n; ++i) c[i] = a[i] + b[i];

    LOG_DEBUG("{}", c[(int)Rand::random(0.f, n - 1.f)]);

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
