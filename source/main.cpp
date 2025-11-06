#include "integrations.hpp"
#include "worlds.hpp"
#include <cmath>
#include <cstdlib>
#include <functional>
#include "timing.h"
#include <iomanip>
#include <iostream>

int clear_icache() {
    long long out = 0;
    const size_t bigger_than_cachesize = 10 * 1024 * 1024;
    long *p = new long[bigger_than_cachesize];
    for(int i = 0; i < bigger_than_cachesize; i++) {
        p[i] = rand();
    }

    for(int i = 0; i < bigger_than_cachesize; i++) {
        out += p[i];
    }

    delete[] p;
    return out;
}

template <typename T, typename Time, typename... Targs>
void test_perf(std::function<T> func, int k, Targs... args) {
    Time numerator{};

    auto t1 = curr_time();
    for (int i = 0; i < k; ++i) {
        func(args...);
    }
    auto t2 = curr_time();
    numerator = diff_time<Time>(t1, t2);

    auto denominator = (Time)k;

    std::cout << "Average time: " << numerator.count() / denominator.count() << '\n';
}

int main() {
    // std::function<int(int)> fac = [&](int n) {return (n < 2) ? 1 : n * fac(n - 1); };
    std::function<int(int)> fib = [&](int n) {return (n < 2) ? 1 : fib(n - 2) + fib(n - 1); };

    int depth = 10;
    using tick = nanoseconds;

    auto samples{1000000};
    auto lower{0};
    auto upper{5};
    auto func = [](double x) { return pow(x, 2) + pow(x, 3) - exp(-x); };
    auto funcStr = "x^2 + x^3 - e^-x";

    auto t1 = curr_time();
    auto monte_res = test_integrator(monte_carlo, func, lower, upper, samples); 
    auto t2 = curr_time();
    auto diff1 = diff_time<tick>(t1, t2);

    auto t3 = curr_time();
    auto trapezoidal_res = test_integrator(trapezoidal, func, lower, upper, samples); 
    auto t4 = curr_time();
    auto diff2 = diff_time<tick>(t3, t4);

    std::cout << "Monte carlo from " << lower << " to " 
              << upper << " of " << funcStr << " with " << samples << " samples: "
              << std::setprecision(10) << monte_res << "\t time: " 
              << diff1.count() << "ns\n";

    std::cout << "Trapezoidal from " << lower << " to "
              << upper << " of " << funcStr << " with " << samples << " samples: " 
              << std::setprecision(10) << trapezoidal_res << "\t time: " 
              << diff2.count() << "ns\n";

    std::cout << "Time difference 1" << diff1.count() - diff2.count() << '\n';

    auto p = variance_test(monte_carlo, func, lower, upper, 1000000, 100, trapezoidal_res);
    std::cout << p.first << ' ' << p.second;

    return 0;
}
