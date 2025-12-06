
Confidence intervals (CIs) all have the same general shape:

$$
\text{estimate} \;\pm\; (\text{critical value}) \times (\text{standard error})
$$

Below are the main CIs you need:

- Population mean ($\sigma$ **known**)
- Population mean ($\sigma$ **unknown**)
- Population proportion $p$
- Population variance $\sigma^2$ and standard deviation $\sigma$

---

## 1. CI for a Population Mean, $\sigma$ Known (Z-Interval)

### Setup

- Data: $X_1, \dots, X_n$ is a random sample from a population with mean $\mu$ and **known** variance $\sigma^2$.
- Often assume:
  - Either population is normal, **or**
  - $n$ is large so CLT makes $\bar{X}$ approximately normal.

Define:

- Sample mean:
  $$
  \bar{X} = \frac{1}{n} \sum_{i=1}^n X_i
  $$

### Distribution / Pivot

When $\sigma$ is known:

$$
Z = \frac{\bar{X} - \mu}{\sigma / \sqrt{n}} \sim \mathcal{N}(0,1)
$$

### $(1 - \alpha)$ CI for $\mu$

A $100(1-\alpha)\%$ CI for $\mu$ is:

$$
\bar{X} \pm z_{\alpha/2} \cdot \frac{\sigma}{\sqrt{n}}
$$

In practice, plug in the sample mean $\bar{x}$:

$$
\boxed{
\text{CI for } \mu:\quad 
\bar{x} \pm z_{\alpha/2} \cdot \frac{\sigma}{\sqrt{n}}
}
$$

Where:

- $z_{\alpha/2}$ = standard normal critical value with right-tail area $\alpha/2$.

---

## 2. CI for a Population Mean, $\sigma$ Unknown (t-Interval)

### Setup

- Data: $X_1, \dots, X_n$ is a random sample from a population with mean $\mu$ and **unknown** variance $\sigma^2$.
- Often assume population is approximately **normal** (especially important for small $n$).

Define:

- Sample mean:
  $$
  \bar{X} = \frac{1}{n} \sum_{i=1}^n X_i
  $$
- Sample variance:
  $$
  S^2 = \frac{1}{n-1}\sum_{i=1}^n (X_i - \bar{X})^2
  $$

### Distribution / Pivot

When $\sigma$ is unknown and data are normal:

$$
T = \frac{\bar{X} - \mu}{S / \sqrt{n}} \sim t_{n-1}
$$

### $(1 - \alpha)$ CI for $\mu$

A $100(1-\alpha)\%$ CI for $\mu$ is:

$$
\bar{X} \pm t_{\alpha/2, \, n-1} \cdot \frac{S}{\sqrt{n}}
$$

In practice:

$$
\boxed{
\text{CI for } \mu:\quad
\bar{x} \pm t_{\alpha/2, \, n-1} \cdot \frac{s}{\sqrt{n}}
}
$$

Where:

- $t_{\alpha/2, \, n-1}$ is the **Student’s t** critical value with
  - df $= n-1$,
  - right-tail area $\alpha/2$.

---

## 3. CI for a Population Proportion $p$

### Setup

- Each observation is success/failure (Bernoulli).
- $X_1, \dots, X_n$ i.i.d. Bernoulli$(p)$.
- Let total number of successes be:
  $$
  X = \sum_{i=1}^n X_i
  $$
- Sample proportion:
  $$
  \hat{p} = \frac{X}{n}
  $$

For large $n$, by CLT:

$$
\hat{p} \approx \mathcal{N}\left(p,\; \frac{p(1-p)}{n}\right).
$$

We estimate $p$ by $\hat{p}$ inside the standard error.

### $(1 - \alpha)$ CI for $p$

Approximate CI:

$$
\hat{p} \pm z_{\alpha/2} \cdot \sqrt{\frac{\hat{p}(1 - \hat{p})}{n}}
$$

So:

$$
\boxed{
\text{CI for } p:\quad
\hat{p} \pm z_{\alpha/2} \sqrt{\frac{\hat{p}(1 - \hat{p})}{n}}
}
$$

Common “large-sample” conditions (for using this CI):

- $n\hat{p} \ge 10$ and $n(1 - \hat{p}) \ge 10$
  (your course might use 5 or 10; check STAT 400 notes).

---

## 4. CI for Population Variance $\sigma^2$ and SD $\sigma$

### Setup

- Data: $X_1, \dots, X_n$ is a random sample from a **normal** population with variance $\sigma^2$.
- Sample variance:
  $$
  S^2 = \frac{1}{n-1}\sum_{i=1}^n (X_i - \bar{X})^2
  $$

Key fact:

$$
\frac{(n - 1)S^2}{\sigma^2} \sim \chi^2_{n-1}
$$

### 4.1 $(1 - \alpha)$ CI for Variance $\sigma^2$

Let $\nu = n - 1$. Then a $100(1-\alpha)\%$ CI for $\sigma^2$ is:

$$
\left(
\frac{(n-1)S^2}{\chi^2_{\alpha/2, \, \nu}}
\;,\;
\frac{(n-1)S^2}{\chi^2_{1-\alpha/2, \, \nu}}
\right)
$$

In practice:

$$
\boxed{
\text{CI for } \sigma^2:\quad
\left(
\frac{(n-1)s^2}{\chi^2_{\alpha/2, \, n-1}},
\;
\frac{(n-1)s^2}{\chi^2_{1-\alpha/2, \, n-1}}
\right)
}
$$

Where:

- $\chi^2_{\alpha/2, \, n-1}$ is the chi-square critical value such that  
  $P(Y \ge \chi^2_{\alpha/2, \, n-1}) = \alpha/2$ for $Y \sim \chi^2_{n-1}$.
- $\chi^2_{1-\alpha/2, \, n-1}$ is such that  
  $P(Y \le \chi^2_{1-\alpha/2, \, n-1}) = 1 - \alpha/2$.

### 4.2 CI for Standard Deviation $\sigma$

To get a CI for $\sigma$, just take square roots of the variance endpoints.

If:

$$
\left(L_{\sigma^2}, U_{\sigma^2}\right)
$$

is a CI for $\sigma^2$, then:

$$
\boxed{
\text{CI for } \sigma:\quad
\left(\sqrt{L_{\sigma^2}}, \sqrt{U_{\sigma^2}}\right)
}
$$

Equivalently, directly from the variance CI formula:

$$
\boxed{
\text{CI for } \sigma:\quad
\left(
\sqrt{\frac{(n-1)s^2}{\chi^2_{\alpha/2, \, n-1}}},
\;
\sqrt{\frac{(n-1)s^2}{\chi^2_{1-\alpha/2, \, n-1}}}
\right)
}
$$

---

## 5. Mini Formula Summary (Fast Review)

### Mean, $\sigma$ known

$$
\bar{x} \pm z_{\alpha/2} \cdot \frac{\sigma}{\sqrt{n}}
$$

### Mean, $\sigma$ unknown

$$
\bar{x} \pm t_{\alpha/2, \, n-1} \cdot \frac{s}{\sqrt{n}}
$$

### Proportion $p$

$$
\hat{p} \pm z_{\alpha/2} \sqrt{\frac{\hat{p}(1-\hat{p})}{n}}
$$

### Variance $\sigma^2$

$$
\left(
\frac{(n-1)s^2}{\chi^2_{\alpha/2, \, n-1}},
\;
\frac{(n-1)s^2}{\chi^2_{1-\alpha/2, \, n-1}}
\right)
$$

### Standard deviation $\sigma$

$$
\left(
\sqrt{\frac{(n-1)s^2}{\chi^2_{\alpha/2, \, n-1}}},
\;
\sqrt{\frac{(n-1)s^2}{\chi^2_{1-\alpha/2, \, n-1}}}
\right)
$$


