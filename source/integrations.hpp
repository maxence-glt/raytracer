#pragma once

#include <functional>

/* integrand takes in x and returns f(x) */
using integrand = std::function<double(double)>;
/* 
 * integral takes in an integrand, an upper and lower bound, and the samples
 * becaue we're doing numerical integration, we need a sample count
 * returns the integral estimate
*/
using samples = std::size_t;
using integral = std::function<double(integrand, double, double, samples)>;

double monte_carlo(const integrand &func, double lower, double upper, samples samples);
double trapezoidal(const integrand &func, double lower, double upper, samples samples);
double monte_carlo_stratified(const integrand &func, const double a, const double b, const samples n);
double test_integrator(const integral &integral, const integrand &func, double lower, double upper, samples samples);

//  return {mean, mse};
std::pair<double,double> variance_test(const integral &method, const integrand &func,
                                       double a, double b, samples n,
                                       std::size_t trials, double true_I);
