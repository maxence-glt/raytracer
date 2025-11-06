#include "integrations.hpp"
#include "util.h"
#include "main.h"

/*
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
*/

double monte_carlo(const integrand &func, 
                   const double a, const double b, const samples n) {
    double sum{};

    for (int i = 1; i <= n; ++i) {
        auto sample = random_double(a, b);
        sum += func(sample);
    }

    sum *= ((b - a) / n);
    return sum;
}

double monte_carlo_stratified(const integrand &func, 
                              const double a, const double b, const samples n) {
    if (n == 0) return 0.0;

    double sum{};
    int h = 100000;
    if (h > n) h = n;

    const double w = (b - a) / static_cast<double>(h);
    const std::size_t base = n / h;
    std::size_t rem = n % h;
    int n_h = n / h;

    for (int s = 1; s <= h; ++s) {
        double strata_a = a + (s-1)*w;
        double strata_b = strata_a + w;

        std::size_t ns = base + (s < rem ? 1u : 0u);
        if (ns == 0) continue;

        double stratum_sum{};
        for (int i = 1; i <= ns; ++i) {
            auto sample = random_double(strata_a, strata_b);
            stratum_sum += func(sample);
        }
        sum += w * (stratum_sum / static_cast<double>(ns));
    }

    return sum;
}

double trapezoidal(const integrand &func, 
                   const double a, const double b, const samples n) {
    double sum{};
    double l{};
    double dx = (b - a) / n;

    for (int i = 1; i <= n - 1; ++i)
        sum += func(a + (i * dx));

    double outer = (func(a) + func(b)) / 2;

    return (outer + sum) * dx;
}

// PBRT exercise 2.1
double test_integrator(const integral &method, const integrand &func, 
                       const double a, const double b, const samples n) {
    auto result = method(func, a, b, n);
    return result;
}

// PBRT exercise 2.2
std::pair<double, double> variance_test(const integral &method, const integrand &func,
                                        const double a, const double b, 
                                        const samples n, const std::size_t trials,
                                        const double true_I) {
    double mean = 0.0;
    double mse = 0.0;

    for (std::size_t t = 0; t < trials; ++t) {
        double est = method(func, a, b, n);
        mean += est;
        double err = est - true_I;
        mse += err * err;
    }

    mean /= static_cast<double>(trials);
    mse /= static_cast<double>(trials);
    return {mean, mse};
}
