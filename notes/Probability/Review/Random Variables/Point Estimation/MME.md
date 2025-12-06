**Method of Moments Estimation**
[[Moments]]

Match **sample moments** to **theoretical moments**
- The $k$-th **population moment**: $\mu_k'=E(X^k)$
- The $k$-th **sample moment**: $m_k=\frac{1}{n}\sum_{i=1}^{n}X_i^k$

If the distribution has $r$ unknown parameters, we:
1. Write the first $r$ population moments in terms of parameters, set them equal to the first $r$ sample moments.
	1. Set the first sample moment equal to the first theoretical moment: $\frac{1}{n}\sum X_i\equiv E[X]$
	2. Set the second sample moment equal to the second theoretical moment: $\frac{1}{n}\sum X_i^2\equiv E[X^2]$
	3. And on and on for as many parameters that need estimation
2. Solve the system for the parameters.

That solution gives the **method of moments estimators** (MMEs)

## MME (Method of Moments) Examples

### Example 1 – MME for $p$ in Bernoulli

For a Bernoulli$(p)$ random variable:

- Population mean: $\mathbb{E}[X] = p.$  
- First sample moment: $m_1 = \bar{X} = \dfrac{1}{n}\sum_{i=1}^n X_i.$

Method of moments sets $m_1 = \mathbb{E}[X]$:

$\bar{X} = p \Rightarrow \hat{p}_{\text{MME}} = \bar{X}.$

Here, MME and MLE agree.

---

### Example 2 – MME for $\lambda$ in Exponential$(\lambda)$

For Exponential$(\lambda)$:

- Population mean: $\mathbb{E}[X] = \dfrac{1}{\lambda}.$  
- First sample moment: $m_1 = \bar{X}.$

Set $m_1 = \mathbb{E}[X]$:

$\bar{X} = \dfrac{1}{\lambda} \Rightarrow \hat{\lambda}_{\text{MME}} = \dfrac{1}{\bar{X}}.$

Again, same as the MLE.

---

### Example 3 – MME for Normal$(\mu, \sigma^2)$

Assume $X \sim N(\mu, \sigma^2)$ with both $\mu$ and $\sigma^2$ unknown.

Population moments:

- First moment: $\mathbb{E}[X] = \mu.$  
- Second moment: $\mathbb{E}[X^2] = \mu^2 + \sigma^2.$

Sample moments:

- $m_1 = \bar{X} = \dfrac{1}{n}\sum_{i=1}^n X_i.$  
- $m_2 = \dfrac{1}{n}\sum_{i=1}^n X_i^2.$

Method of moments equations:

1. $m_1 = \mathbb{E}[X] \Rightarrow \bar{X} = \mu \Rightarrow \hat{\mu}_{\text{MME}} = \bar{X}.$  
2. $m_2 = \mathbb{E}[X^2] \Rightarrow m_2 = \mu^2 + \sigma^2.$

Substitute $\hat{\mu} = \bar{X}$ into the second:

$m_2 = \bar{X}^2 + \sigma^2 \Rightarrow \hat{\sigma}^2_{\text{MME}} = m_2 - \bar{X}^2.$

So the MMEs are:

- $\hat{\mu}_{\text{MME}} = \bar{X}.$  
- $\hat{\sigma}^2_{\text{MME}} = m_2 - \bar{X}^2.$

---