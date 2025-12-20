#### Bernoulli Distribution
> A random experiment where the outcome can be classified as one of two mutually exclusive ways. A sequence of Bernoulli trials occurs when a Bernoulli experiment is performed several **independent** times, and the success probability, _p_, remains the same

$$
\begin{aligned}
f(x) &= p^{x}(1-p)^{1-x}, \quad x \in \{0,1\} \\
\mathbb{E}[X] &= \sum_{x=0}^{1} x\, p^{x} (1-p)^{1-x}
= 0\cdot(1-p) + 1\cdot p = p \\
\operatorname{Var}(X) &= \sum_{x=0}^{1} (x-p)^{2} p^{x} (1-p)^{1-x}
= p(1-p) \\
\operatorname{SD}(X) &= \sqrt{p(1-p)}
\end{aligned}
$$
#### Binomial Distribution
> The probability of getting exactly k successes in n independent Bernoulli trials (with the same rate p) is given by:
$$
\begin{aligned}
X &\sim \operatorname{Binomial}(n,p) \\
f(k) &= \binom{n}{k}\, p^{k} (1-p)^{n-k}, && k = 0,1,2,\ldots,n \\
\mathbb{E}[X] &= np \\
\operatorname{Var}(X) &= np(1-p)\\
\end{aligned}
$$
#### Negative Binomial Distribution
> The distribution of a number of failures $k$ before observing $r^{th}$ success when observing independent Bernoulli trials with probability of success $p$.
$$
\begin{aligned}
X &\sim \operatorname{NegBin}(r,p) \\
f(k) &= \binom{k-1}{r-1}\, p^{r} (1-p)^{k-r}, \quad k = r, r+1, r+2, \ldots \\
\mathbb{E}[X] &= \frac{r}{p} \\
\operatorname{Var}(X) &= \frac{r(1-p)}{p^{2}}
\end{aligned}
$$
#### Geometric Distribution
> Say we observe a sequence of independent Bernoulli trials until the first success occurs. If X is the number of trials needed to observe the first success, then X follows a **Geometric Distribution** with parameter p.
$$
\begin{aligned}
X &\sim \operatorname{Geom}(p) \\
f(x) &= p(1-p)^{x-1}, && x = 1,2,3,\ldots \\
\mathbb{E}[X] &= \frac{1}{p} \\
\operatorname{Var}(X) &= \frac{1-p}{p^{2}}
\end{aligned}
$$

>The geometric distribution is a special case of the negative binomial distribution where you are waiting for only **one success**. The negative binomial distribution is a generalization that counts the number of trials needed to get a fixed number of successes (r).
#### Hypergeometric Distribution

> The hypergeometric distribution is a discrete probability distribution that describes the probability of $k$ successes (random draws for which the object drawn has a specified feature) in $n$ draws, _without_ replacement, from a finite population of size $N$ that contains exactly $K$ objects with that feature, where in each draw is either a success or a failure.
> 
> In contrast, the **binomial distribution** describes the probability of $k$ successes in $n$ draws _with_ replacement. 
> 
> **Replacement** refers to the process of returning a selected item to the population before the next item is drawn, allowing the same item to be selected multiple times

$$
\begin{aligned}
&N = N_{1} + N_{2}, \qquad X \sim \operatorname{Hypergeometric}(N, N_{1}, n) \\
f(x) &= \frac{\binom{N_{1}}{x}\binom{N_{2}}{\,n-x\,}}{\binom{N}{n}},
\quad x \le n,\; x \le N_{1},\; n-x \le N_{2} \\
\mathbb{E}[X] &= n\,\frac{N_{1}}{N} \\
\operatorname{Var}(X) &= n\,\frac{N_{1}}{N}\,\frac{N_{2}}{N}\,\frac{N-n}{N-1}
\end{aligned}
$$
#### Multinomial Distribution

> Similar to binomial distribution but for more than two outcomes.

$$
\begin{aligned}
&\text{Parameters: } n,\; p_1,p_2,\ldots,p_k,\quad \sum_{i=1}^k p_i = 1 \\[2pt]
\mathbf{X} &=(X_1,\ldots,X_k) \sim \operatorname{Multinomial}(n; p_1,\ldots,p_k) \\[4pt]
f(\mathbf{x}) &= \frac{n!}{x_1!\,x_2!\cdots x_k!}\; p_1^{x_1} p_2^{x_2}\cdots p_k^{x_k}, \\
&\qquad x_i \in \{0,1,2,\ldots\},\ \sum_{i=1}^k x_i = n \\[4pt]
\mathbb{E}[X_i] &= n p_i \\[2pt]
\operatorname{Var}(X_i) &= n p_i (1 - p_i)
\end{aligned}
$$

#### Poisson Distribution

> The **Poisson distribution** is a discrete probability distribution that expresses the probability of a given number of events occurring in a **fixed interval of time** if these events occur with a known **constant mean rate** and **independently** of the time since the last event
> 
> Under a Poisson distribution with the expectation of $\lambda$ events in a given interval, the probability of $k$ events in the same interval is:

$$
\begin{aligned}
X &\sim \operatorname{Poisson}(\lambda) \\
f(k) &= \frac{\lambda^{k} e^{-\lambda}}{k!}, && k = 0,1,2,\ldots \\
\mathbb{E}[X] &= \lambda \\
\operatorname{Var}(X) &= \lambda
\end{aligned}
$$
#### Exponential Distribution

> Consider a Poisson with an expected number of occurrences $\lambda$ in a given interval
> 
> If we count the number of these occurrences, this number will be a random variable $X$ ~ $Poission(\lambda)$
> 
> Let $W$ be the waiting time until the first occurrence. Then $W$ follows an **exponential distribution**

$$
\begin{aligned}
&\text{We often parameterize with } \theta = 1/\lambda.\\[2pt]
X &\sim \operatorname{Exp}(\theta) \\
f(x) &= \frac{1}{\theta}\, e^{-x/\theta}, \qquad 0 \le x < \infty \\[2pt]
F(x) &= 1- e^{-x/\theta}, \qquad 0 \le x < \infty \\[2pt]
\mathbb{E}[X] &= \theta \\[2pt]
\operatorname{Var}(X) &= \theta^{2}
\end{aligned}
$$

#### Uniform Distribution

> A continuous random variable $X$ has a **uniform distribution** if its [[Probability Density Function|PDF]] is equal to a constant on its support

$$
\begin{aligned}
f(x)=\frac{1}{b-a}, \quad a \leq x \leq b \\
E[X] = \frac{a+b}{2} \\
Var[X]=\frac{(b-a)^2}{12}
\end{aligned}
$$
#### Memoryless Property
*Discrete Memorylessness*
if $X$ is the **total** number of trials required for the first success
$$
P[X\gt m+n|X\ge m]=P[X\ge n]
$$
*Continuous Memorylessness*
If $X$ is the **total** time required for the first success
$$
P[X\gt t + s | X \ge t] = P[X\gt s]
$$
#### Gamma Distribution
>Consider a Poisson process with rate $\lambda$
>A random variable measuring the waiting time until the first occurrence is Exponential($\theta=1/\lambda$)
>
>Let a random variable $X$ denote the waiting time until the $\alpha$-th occurrence
>The $X$ follows a Gamma distribution with parameters $\alpha$ and $\theta$
$$
\begin{aligned}
X &\sim \operatorname{Gamma}(\alpha,\theta) \\[2pt]
f(x) &= \frac{1}{\Gamma(\alpha)\,\theta^{\alpha}}\, x^{\alpha-1} e^{-x/\theta},
\qquad 0 \le x < \infty \\[4pt]
\mathbb{E}[X] &= \alpha\theta \\[2pt]
\operatorname{Var}(X) &= \alpha\theta^{2}
\end{aligned}
$$
#### [[Normal Distribution]]

> Symmetric distribution with a central peak, tails that taper off

![[Pasted image 20251104221019.png]]
$$
\begin{aligned}
X &\sim \mathcal{N}(\mu,\sigma^{2}) \\
\large f(x) &= \huge \frac{1}{\sqrt{2\pi\sigma^{2}}}e^{\!\left(-\frac{(x-\mu)^{2}}{2\sigma^{2}}\right)}
\quad -\infty < x < \infty \\
\mathbb{E}[X] &= \mu \\
\operatorname{Var}(X) &= \sigma^{2}
\end{aligned}
$$
#### [[Joint probability distribution]]
