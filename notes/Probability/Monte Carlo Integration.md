[[Probability Review]]

The Monte Carlo estimator approximates the value of an arbitrary integral:

Given 
- a 1D integral $\int_a^b f(x)dx$ 
- a supply of independent uniform random variables, $X_i \in [a,b]$

$\huge F_n = \frac{b-a}{n}\sum_{i=1}^{n} f(X_i)$

$E[F_n]$ is equal to the integral.

Extending this estimator to multiple dimensions:

$\huge\int_{z_0}^{z_1}\!\int_{y_0}^{y_1}\!\int_{x_0}^{x_1} f(x,y,z)\,dx\,dy\,dz.$

$\huge p(X)=\frac{1}{(x_1-x_0)}\frac{1}{(y_1-y_0)}\frac{1}{(z_1-z_0)}$ (PDF)

$\huge\frac{(x_1-x_0)(y_1-y_0)(z_1-z_0)}{n}\sum_{i=1}^{n} f(X_i)$

The restriction to uniform random variables can be relaxed with a small generalization. If the random variables are drawn from a PDF this estimator can be used:

$\huge F_n = \frac{1}{n}\sum_{i=1}^{n} \frac{f(X_i)}{p(X_i)}$

### Sampling techniques
Sampling is about selecting units out of some population of interest to make some statement about the whole. 

For example, if you just shoot one ray into the scene per pixel, you'll get hard edges around object boundaries (aliasing). That's because the sampling rate isn't high enough. Instead, you can shoot multiple rays per pixel, into slightly different directions, and average them. That's also analogous to what supersampling anti-aliasing in video games does, although in raytracing we usually include some randomness in the ray directions to arrive at a better result with fewer rays.

[[Stratified Sampling]]
[[Importance Sampling]]
While [[Russian Roulette]] reduces the number of samples, [[Splitting]] improves efficiency.
[[Inversion Transform Sampling]]
