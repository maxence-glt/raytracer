Characterize a random variable by location (**mean**, **median**) and how spread out it is (**variance**)

For a **discrete** random variable, $X$, we can say $Var[X], \sigma^2$, or $\sigma^{2}_{X}$

$$\sigma^2=E[X^2]-(E[X])^2$$
and standard deviation being $SD[X]=\sqrt{\sigma^2}$

For a **continuous** random variable, 
$$\sigma^2=E[(X-\mu)^2]=\int_{-\infty}^{\infty}(x-\mu)^2f(x)dx$$
**Linear Combination:**
$$
\sigma^2(aX+b)=a^2\sigma^2_x
$$
$$
\sigma(aX+b)=|a|\sigma(X)
$$