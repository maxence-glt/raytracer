Russian roulette is a technique that can improve the efficiency of Monte Carlo estimates by skipping the evaluation of samples that would make a small contribution to the final result. 

In rendering, we often have estimators of the form
$$\frac{f(X)~v(x)}{p(x)}$$
where the integrand consists of some factors $f(X)$ that are easily evaluated
- like those that relate to how the surface scatters light

and others that are more expensive to evaluate, such as a binary visibility factor $v(X)$ that requires tracing a ray
- in these cases, most of the computational expense of evaluating the estimator lies in $v$

To apply Russian roulette, we select some termination probability $q$. 

With probability $q$, the estimator is not evaluated for the particular sample, and some constant value $c$ is used in its place ($c=0$ is often used). With probability $1-$, the estimator is still evaluated but is weighted by the factor $1/(1-q)$, which effectively compensates for the samples that were skipped.

$$
F' =
\begin{cases}
\frac{F - q c}{1 - q}, & \xi > q,\\
c, & \text{otherwise.}
\end{cases}
$$
Russian roulette never reduces variance. However, it does improve Monte Carlo efficiency if the probabilities are chosen so that samples that are likely to make a small contribution to the final result are skipped.