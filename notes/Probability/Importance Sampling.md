A [[Monte Carlo Integration|Monte Carlo method]] for evaluating properties of a particular distribution, while only having samples generated from a different distribution than the distribution of interest

$\huge F_n = \frac{1}{n}\sum^n_{i=1}\frac{f(X_i)}{p(X_i)}$ (Monte Carlo estimator)

The monte carlo estimator above converges more quickly if the samples are taken from a distribution $p(x)$ that is similar to the function $f(x)$ in the integrand.

For examples, the Gaussian function $f(x)=e^{-1000(x-1/2)^2}$ is close to zero over most of the domain $[0, 1)$. Samples $X$ with $X<0.2$ or $x>0.3$ are of little help in estimating the value of the integral since they give no information about the magnitude of the bump in the function’s value around $1/4$.

If samples are instead drawn from the piecewise-constant distribution
$$
p(x)=
\begin{cases}
0.1, & x \in [0,0.45),\\
9.1, & x \in [0.45,0.55)\\
0.1, & x \in [0.55,1)
\end{cases}
$$

![[Pasted image 20251019175500.png]]
![[Pasted image 20251019175506.png]]
![[Pasted image 20251019175519.png]]
1. A narrow Gaussian function that is close to zero over most of the range $[0, 1]$. The basic Monte Carlo estimator of Equation has relatively high variance if it is used to integrate this function, since most samples have values that are close to zero. 
2. A PDF that roughly approximates the function’s distribution. If this PDF is used to generate samples, variance is reduced substantially. 
3. A representative distribution of samples generated according to (2)