To evaluate the [[Monte Carlo Integration|Monte Carlo]] estimator in Equation, it is necessary to be able to draw random samples from a chosen probability distribution

Inversion transform sampling (AKA *inversion sampling, inverse probability integral transform, inverse transformation method, Smirnov transform*), is a basic method for pseudo-random number sampling.

It maps uniform samples from $[0,1)$ to a given 1D probability distribution by inverting the distribution’s CDF. [[Canonical Uniform Random Variable]]

The discrete CDF is given by:
$$P_i=\sum_{j=1}^{i}p_j$$
The sampling operation
$$
\sum_{j=1}^{i-1} p_j \le \xi < \sum_{j=1}^{i} p_j .
$$
can be expressed by finding $i$ such that 
$$P_{i-1} \leq \xi \le P_i$$
which can be interpreted as inverting the CDF $P$, and thus, the name of the technique.

In PBRT, they use `SampleDiscrete()` to implement this algorithm. 
- It takes
	- a not-necessarily normalized set of nonnegative weights `weights`
	- a uniform random sample `u`
	- **Optional** return the value of the PMF
	- **Optional** return new uniform random sample that is derived from u
- Returns the index of one of the weights with probability proportional to its weight

It finds `i` such that
$$\sum_{j=1}^{i-1} w_j \le \xi\sum w_i < \sum_{j=1}^{i} w_j $$
This function is designed for the case where only a single sample needs to be generated from the weights’ distribution; if multiple samples are required, the [AliasTable](https://www.pbr-book.org/4ed/Sampling_Algorithms/The_Alias_Method.html#AliasTable), should generally be used instead

PseudoCode:
```cpp
int SampleDiscrete(const std::span<float> &weights, float u, float *pmf, float *uRemapped) {
    <<Handle empty weights for discrete sampling>>      
    <<Compute sum of weights>>      
    <<Compute rescaled u prime sample>>      
    <<Find offset in weights corresponding to u prime >>
    <<Compute PMF and remapped u value, if necessary>>      
    return offset;
```

### Continuous Case
What happens as the number of discrete possibilities approaches infinity?
- The PMF becomes a PDF, and the CDF becomes its integral.

*Aside*
CDF vs PDF

PDF (Probability Density Function) is used for continuous random variables to find the probability of a value falling within a specific range, while CDF (Cumulative Distribution Function) calculates the probability that a random variable will be less than or equal to a given value and applies to both continuous and discrete variables

![[Pasted image 20251023002536.png]]

We can draw a sample $X$ from a PDF $p(x)$ with the following steps
1. Integrate the PDF to find the CDF $P(X)=\int_{0}^{x} p(x')dx'$
2. Obtain a uniformly distributed random number $\xi$
3. Generate a sample by solving $\xi=P(X)$ for $X$; in other words, find $X=P^{-1}(\xi)$

### Sampling a Linear Function
More discussed in [[Linear Interpolation|here]]