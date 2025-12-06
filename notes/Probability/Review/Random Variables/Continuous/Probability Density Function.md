A PDF $f(x)$ is an integrable function that satisfies the following three conditions
1. $f(x)\geq 0, x \in S$
2. $\int_S f(x)dx=1$
3. If $(a, b)\subseteq S$, then the probability of the event $[a < X < b]$ is$$ P(a < X < b) = \int_a^b f(x)dx$$
Use the [[Cumulative Distribution Function|CDF]] to calculate probabilities.
#### Properties
- As oppose to discrete rv's needing their [[Probability Mass Function|PMFs]] to be bounded by 1, continuous PDFs do not need to be bounded ($f(x)$ can be larger than 1)
- However, total area between a PDF and the x-axis is equal to 1

#### Percentiles
The (100p)$^{th}$ percentile is a number $\pi_p$ such that the area under $f(x)$ to the left of $\pi_p$ is $p$
$$p=\int_{-\infty}^{\pi_p} f(x)dx=F(\pi_p)$$
