#include "integrations.hpp"
#include "util/timing.hpp"
#include "worlds.hpp"
#include "util/vecmath.hpp"
#include "util/error.hpp"
#include "util/log.hpp"
#include "util/math.hpp"
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    /*
    size_t samples{1000000};
    auto lower{0};
    auto upper{5};
    auto func = [](double x) { return pow(x, 2) + pow(x, 3) - exp(-x); };
    auto trapezoidal_res = test_integrator(trapezoidal, func, lower, upper, samples); 

    auto t1 = curr_time();
    auto trap_var = variance_test(trapezoidal, func, lower, upper, samples, 10, trapezoidal_res);
    auto t2 = curr_time();

    auto t3 = curr_time();
    auto p = variance_test(monte_carlo, func, lower, upper, samples, 10, trapezoidal_res);
    auto t4 = curr_time();

    auto t5 = curr_time();
    auto p_strat = variance_test(monte_carlo_stratified, func, lower, upper, samples, 10, trapezoidal_res);
    auto t6 = curr_time();

    std::cout << std::setprecision(10) << "Trapezoidal mean " << trap_var.first << " samples: " << trap_var.second
              << " in " << diff_time<milliseconds>(t1, t2).count() << '\n';

    std::cout << std::setprecision(10) << "Monte Carlo mean: " << p.first << " and variance: " << p.second
              << " in " << diff_time<milliseconds>(t3, t4).count() << '\n';

    std::cout << std::setprecision(10) << "Monte Carlo with stratified mean: "
              << p_strat.first << " and variance: " << p_strat.second
              << " in " << diff_time<milliseconds>(t5, t6).count() << '\n';

    const int N = 10000000;
    std::vector<int> arr(N, 1);
    std::vector<int> arr2(N, 1);

    volatile int total{};
    auto f1 = curr_time();
    for (int i = 0; i < arr.size(); ++i)
        total += arr[i];
    auto f2 = curr_time();

    auto r1 = curr_time();
    for (int i = arr.size() - 1; i >= 0; --i)
        total += arr2[i];
    auto r2 = curr_time();

    std::cout << diff_time<nanoseconds>(f1, f2).count() << '\n';
    std::cout << diff_time<nanoseconds>(r1, r2).count();
    */

    initLogging(LogLevel::Verbose, "manyBalls", true);
    LOG_VERBOSE("Starting raytracing:");
    many_balls();
    //testErrors();

    LOG_VERBOSE("Finished render succesfully, shutting down logging\n\n******************************************************\n\n");

    return 0;
}
