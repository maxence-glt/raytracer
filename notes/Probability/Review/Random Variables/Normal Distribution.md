$$\begin{aligned}
X &\sim \mathcal{N}(\mu,\sigma^{2}) \\
\large f(x) &= \huge \frac{1}{\sqrt{2\pi\sigma^{2}}}e^{\!\left(-\frac{(x-\mu)^{2}}{2\sigma^{2}}\right)}
\quad -\infty < x < \infty \\
\mathbb{E}[X] &= \mu \\
\operatorname{Var}(X) &= \sigma^{2}
\end{aligned}$$
### Linear Transformation Theorem

Let $X \sim \mathcal{N}(\mu, \sigma^2)$. Then for constants $\alpha, \beta$,

$$
Y = \alpha X + \beta
$$

also follows a normal distribution:

$$
Y \sim \mathcal{N}(\alpha \mu + \beta,\ \alpha^2 \sigma^2).
$$

We can convert any normal distribution to the standard normal by subtracting the mean and dividing by the standard deviation:

$$
Z = \frac{X - \mu}{\sigma}.
$$

Using this theorem, we can see that

$$
Z \sim \mathcal{N}(0,1).
$$

> What is $z$? 
> 
> The value z gives the number of standard deviations the particular value of C lies above or below the mean $\mu$
> 
> Once you have a _z_ score, you can look up the corresponding probability in a **_z_** **table**
### Sample Mean of Normal random variables 
If $X_1, X_2, \ldots, X_n$ are $n$ mutually independent normal variables with means

$\mu_1, \mu_2, \ldots, \mu_n$ and variances $\sigma_1^2, \sigma_2^2, \ldots, \sigma_n^2$, respectively, then
the linear function  

$$
Y = \sum_{i=1}^n c_i X_i
$$

has the normal distribution  

$$
Y \sim N\left( \sum_{i=1}^n c_i \mu_i,\; \sum_{i=1}^n c_i^2 \sigma_i^2 \right).
$$
### Central Limit Theorem
The **central limit theorem** (CLT) states that, under appropriate conditions, the distribution of a normalized version of the sample mean converges to a standard normal distribution.

If $\bar{X}$ is the mean of a random sample $X_1, X_2, \ldots, X_n$ of size $n$ from a distribution with a finite mean $\mu$ and a finite positive variance $\sigma^2$, then the distribution of  

$$
\large Z = \frac{\bar{X} - \mu}{\sigma / \sqrt{n}}
  = \frac{\sum_{i=1}^n X_i - n\mu}{\sqrt{n}\,\sigma}
$$

is $N(0,1)$ in the limit as $n \to \infty$.

In other words, if $X_1, X_2, \ldots, X_n$ all have mean $\mu$ and variance $\sigma^2$, then  

$$
\bar{X} \sim N\!\left(\mu,\; \frac{\sigma^2}{n}\right).
$$
### Normal Approximation
You start with a **discrete** random variable (values are integers):
- Binomial
- Poisson
When parameters are “large enough”, the distribution of $X$ looks **bell-shaped**, and we approximate:
$$X\approx N(\mu,\sigma^2)$$
where:
- For Binomial: $\mu=np,\sigma^2=np(1-p)$
- For Poisson: $\mu=\lambda, \sigma^2=\lambda$
Then we use **normal distribution tools** (Z-scores, normal tables, etc.) instead of binomial or Poisson formulas, since exact Binomial/Poisson probabilities can be messy for large $n$ or $\lambda$.

##### How it works

Say X is binomial or Poisson and conditions hold ($np \ge 10$ && $n(1-p)\ge10$, or $\lambda\ge10$)
1. Compute mean $\mu$ and SD $\sigma$
2. Standardize
   $$Z=\frac{X-\mu}{\sigma}\approx N(0, 1)$$
3. Probability statements about $X$ become probability statements about $Z$:
   $$P(X\le a)\approx P(Z \le \frac{a-\mu}{\sigma})$$
   $$P(X\ge a)\approx P(Z \ge \frac{a-\mu}{\sigma})$$
   $$P(a\le X \le b)\approx P(\frac{a-\mu}{\sigma} \le Z \le \frac{b-\mu}{\sigma})$$
