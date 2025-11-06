#include <array>
#include <iomanip>
#include <iostream>
#include <random>
#include "integrations.hpp"
#include "util.h"

double monte_carlo(const integrand &func, 
                   const double a, const double b, const double n) {
    double sum{};

    Random<double> r(a, b);

    for (int i = 1; i <= n; ++i) {
        auto sample = r.random();
        sum += func(sample);
    }

    sum *= ((b - a) / n);
    return sum;
}

double trapezoidal(const integrand &func, 
                   const double a, const double b, const double n) {
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
                       const double a, const double b, const double n) {
    auto result = method(func, a, b, n);
    return result;
}

// PBRT exercise 2.2
std::pair<double, double> variance_test(const integral &method, const integrand &func,
                                        const double a, const double b, 
                                        const std::size_t n, const std::size_t trials,
                                        const double true_I) {
    double mean = 0.0;
    double mse = 0.0;

    for (std::size_t t = 0; t < trials; ++t) {
        double est = method(func, a, b, n);
        std::cout << std::setprecision(10) << est << '\n';
        mean += est;
        double err = est - true_I;
        mse += err * err;
    }

    mean /= static_cast<double>(trials);
    mse /= static_cast<double>(trials);
    return {mean, mse};
}
