Sample mean: $\overline{x}=\frac{1}{n}\sum_{i=1}^{n}x_i$
Sample variance: $s^2=\frac{1}{n-1}\sum_{i=1}^{n}(x_i-\overline{x})^2$
Sample standard deviation: $s=\sqrt{s^2}$
 
let's say we are given a distribution, and take random samples from this distribution, but don't know the value of the parameter, $\theta$

>Bernoulli/Binomial: unknown $p$
>Normal: unknown $\mu$, maybe unknown $\sigma^2$
>Exponential: unknown $\lambda$ (rate) or $\theta$=$1/\lambda$ (mean)

>The **parameter space, $\Omega$**, is the range of all possible value of $\theta$

You observe a **sample** $X_1,X_2,...,X_n i.i.d.$, and estimate $\theta$ with $n$ observations $x_1, x_2,...,x_n$
The random variable/statistic, $u(X_1,X_2,...,X_n)$ is an **estimator** or $\theta$
Using the values from the observations, we can find the **estimate** of $\theta, u(x_1, x_2,...,x_n)$

>A **point estimator** is just a function of the sample that gives you a **single number** as your “best guess” of the parameter:

Example:
For a normal with unknown mean $\mu$, the sample mean
$$\overline{X}=\frac{1}{n}\sum_{i=1}^{n}X_i$$
is a point estimator of $\mu$

### Method of Moments Estimation ([[MME]]) $\hat p$
### Method Likelihood Estimation ([[MLE]]) $\hat p$
##### Unbiased Estimators
An estimator $\hat \theta$ of $\theta$ is unbiased if:

$$E(\hat θ)=θ$$

If $E(θ)≠θ$, we say it is **biased**, and the **bias** is:

$$Bias(θ)=E(θ)−\theta$$

##### Mean Squared Error (MSE)
Mean squared error is defined as the expectation of the squared difference of an estimator and the true value. For an unbiased estimator, MSE is equal to the variance; otherwise it is the sum of variance and the squared bias of the estimator.

> $MSE[F] = E[(F - \int f(x)dx)^2]$
> $MSE(\hat\theta)=Bias(\hat\theta,\theta)^2+Var_\theta(\hat\theta)$