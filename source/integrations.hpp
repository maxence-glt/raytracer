#pragma once

#include <functional>

/* integrand takes in x and returns f(x) */
using integrand = std::function<double(double)>;
/* 
 * integral takes in an integrand, an upper and lower bound, and the samples
 * becaue we're doing numerical integration, we need a sample count
 * returns the integral estimate
*/
using integral = std::function<double(integrand, double, double, double)>;

double monte_carlo(const integrand &func, double lower, double upper, double samples);
double trapezoidal(const integrand &func, double lower, double upper, double samples);
double test_integrator(const integral &integral, const integrand &func, double lower, double upper, double samples);

//  return {mean, mse};
std::pair<double, double> variance_test(const integral &method, const integrand &func, 
                                        const double a, const double b, 
                                        const std::size_t n, const std::size_t trials,
                                        const double true_I);
