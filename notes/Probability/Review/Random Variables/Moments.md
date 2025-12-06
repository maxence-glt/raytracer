Moments of a function in mathematics are certain quantitative measures related to the shape of the function's graph

The $r^{th}$ **moment** of a random variable $X$ is $E[X^{r}]$ 
- Also called the **moment about the origin** or the **raw moment**

The $r^{th}$ **central moment** of a [[random variables|random variable]] $X$ is the expected value of the $R^{th}$ power of the deviation of a random variable from its mean $E[(X-\mu_X)^r]$
- Also called the **moment about the mean**

![[Pasted image 20251023230410.png]]

### Moment Generating Function
Let $X$ be a [[Random Variables|discrete random variable]] with [[Probability Mass Function|PMF]] $f(x)$ and space $S$. If there is a positive number $h$ such that 
$$E(e^{tX})=\sum_{x\in S}e^{tx}f(x)$$
exists and is finite for $-h<t<h$, then the function defined by
$$M(t)=E(e^{tX})$$
is called the **moment-generating function (MGF)** of $X$ (or of the distribution of $X$)

>**Example**
>
>If $X$ has the MGF $$
M(t)=e^{t}\left(\frac{3}{6}\right)+e^{2t}\left(\frac{2}{6}\right)+e^{3t}\left(\frac{1}{6}\right), \quad -\infty<t<\infty
$$ then the support of $X$ is $S=\{1,2,3\}$ and the associated probabilities are $$P(X=1)=\frac{3}{6}\quad P(X=2)=\frac{2}{6}\quad P(X=1)=\frac{1}{6}$$

Properties of MGFs
1. If two random variables have the same MGF, then they have the same distributions ([[Probability Mass Function|PMF]], [[Cumulative Distribution Function|CDF]], etc)
2. For two **independent** random variables $X$ and $Y$, the MGF of their sum is the product of their MGFs
   $$M_{x+y}(t)=M_x(t)\cdot M_y (t)$$
3. The $n^{th}$ derivative of $M_x(t)$ evaluated at $t=0$ is equal to the $n^{th}$ moment, $E[X^n]$