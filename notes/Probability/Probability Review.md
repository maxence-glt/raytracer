[PBRT  - Stats](https://www.pbr-book.org/4ed/Monte_Carlo_Integration/Monte_Carlo_Basics)

A **_random variable_** $X$ is a value chosen by some random process. 
Random variables are always drawn from some domain

> Discrete (e.g., a fixed, finite set of possibilities) 
> Continuous (e.g., the real numbers $R$). 

Applying a function $f$ to a random variable $X$ results in a new random variable $Y = f(X)$.

Two random variables are **_independent_** if the probability of one does not affect the probability of the other. In this case, the **_joint probability_** $p(X, Y)$ of two random variables is given by the product of their probabilities:

> $p(X, Y) = p(X)P(Y)$

For **_dependent_** random variables, one’s probability affects the other’s. Consider a bag filled with some number of black balls and some number of white balls. The joint probability $p(X, Y)$ is

> $p(X, Y) = p(X) p(Y|X)$
   where $p(Y|X)$ where is the **_conditional probability_** of $Y$ given a value of $X$

It will often be the case that a random variable’s probability is conditioned on many values. A particularly important random variable is the [[Canonical Uniform Random Variable]]. 

The **_cumulative distribution function_** (CDF) $P(X)$ of a random variable is the probability that a value from the variable’s distribution is less than or equal to some value:

> $P(x) = Pr\{X <= x\}$

**_Continuous random variables_** take on values over ranges of continuous domains 
- (e.g., the real numbers, directions on the unit sphere, or the surfaces of shapes in the scene).
- Beyond $\xi$, another example of a continuous random variable is the random variable that ranges over the real numbers between 0 and 2, where the probability of its taking on any particular value is proportional to the value $2 - x$: it is twice as likely for this random variable to take on a value around 0 as it is to take one around 1, and so forth.

The **_probability density function_** (PDF) formalizes this idea: it describes the relative probability of a random variable taking on a particular value and is the continuous analog of the PMF. The PDF $p(x)$ is the derivative of the random variable’s CDF

> $\large p(x)=\frac{dP(x)}{dx}\,.$

For uniform random variables, $p(x)$ is a constant; this is a direct consequence of uniformity. For $\xi$ we have

> $p(x)=\begin{cases}1, & x\in[0,1)\\0, & \text{otherwise}\end{cases}$

Given an interval in the domain, integrating the PDF gives the probability that a random variable lies inside the interval:

> $\large \Pr\{x\in[a,b]\}=\int_a^b p(x)\,dx = P(b)-P(a)$

The **_expected value_** $E_p[f(x)]$ of a function $f$ is defined as the average value of the function over some distribution of values $p(x)$ over its domain $D$. It is defined as

> $\large \mathbb{E}_p[f(x)] = \int_{D} f(x)\,p(x)\,dx.$

The **_variance_** of an estimator $F$ is defined as

> $V[F]=E[F^2]-E[F]^2$ 

**_Mean squared error_** is defined as the expectation of the squared difference of an estimator and the true value. For an unbiased estimator, MSE is equal to the variance; otherwise it is the sum of variance and the squared bias of the estimator.

> $MSE[F] = E[(F - \int_{} f(x)dx)^2]$

