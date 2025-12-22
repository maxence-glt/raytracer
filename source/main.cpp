#include "integrations.hpp"
#include "util/timing.hpp"
#include "worlds.hpp"
#include "util/vecmath.hpp"
#include "util/error.hpp"
#include "util/log.hpp"
#include "util/math.hpp"
#include "util/vecmath.hpp"
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <cxxabi.h>
#include <vector>
#include "util/check.h"

int main() {
    initLogging(LogLevel::Verbose, "manyBalls", true);
    LOG_VERBOSE("Starting raytracing:");
    //many_balls();
    //testErrors();
    testLogs();

    Vector3i p1(1, 2, 3);
    Vector3i p2(4, 5,  6);
    auto p3 = dot(p1, p2);

    LOG_VERBOSE("Finished render succesfully, shutting down logging\n\n******************************************************\n\n");

    return 0;
}
