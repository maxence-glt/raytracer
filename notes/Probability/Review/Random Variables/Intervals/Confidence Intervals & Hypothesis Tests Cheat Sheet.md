For all of these:

- **Confidence interval (CI)** has the form  
  $$
  \text{estimate} \;\pm\; (\text{critical value}) \times (\text{standard error})
  $$
- **Hypothesis test (HT)** uses a **test statistic**:
  $$
  \text{test stat} = \frac{\text{estimate} - \text{null value}}{\text{standard error}}
  $$

We’ll cover:

1. Population Mean (sigma known; sigma unknown)  
2. Population Proportion  
3. Two Means (sigmas known; sigmas unknown; pooled and unpooled)  
4. Two Proportions  
5. One Variance / Standard Deviation  

---

## 1. Population Mean, $\sigma$ Known

### 1.1 CI for $\mu$ (Z-interval)

- Data: $X_1, \dots, X_n$ from a population with mean $\mu$, **known** $\sigma$.
- Sample mean: $\bar{x}$

CI (confidence level $1 - \alpha$):

$$
\boxed{
\mu \in \bar{x} \pm z_{\alpha/2} \cdot \frac{\sigma}{\sqrt{n}}
}
$$

---

### 1.2 Hypothesis Test for $\mu$ (Z-test)

- Null: $H_0: \mu = \mu_0$
- Alternative (choose one):
  - Two-sided: $H_a: \mu \ne \mu_0$
  - Right-tailed: $H_a: \mu > \mu_0$
  - Left-tailed: $H_a: \mu < \mu_0$

**Test statistic**:

$$
z = \frac{\bar{X} - \mu_0}{\sigma / \sqrt{n}} \sim N(0,1)
$$

**Rejection rules (level $\alpha$)**:

- Two-sided: reject $H_0$ if $|z| > z_{\alpha/2}$
- Right-tailed: reject if $z > z_{\alpha}$
- Left-tailed: reject if $z < -z_{\alpha}$

---

## 2. Population Mean, $\sigma$ Unknown

### 2.1 CI for $\mu$ (t-interval)

- Data: $X_1, \dots, X_n$ from approximately normal population.
- Sample mean: $\bar{x}$, sample standard deviation: $s$.
- Degrees of freedom: $\nu = n - 1$.

CI:

$$
\boxed{
\mu \in \bar{x} \pm t_{\alpha/2,\, n-1} \cdot \frac{s}{\sqrt{n}}
}
$$

---

### 2.2 Hypothesis Test for $\mu$ (t-test)

- Null: $H_0: \mu = \mu_0$
- Alternative: same forms as above.

**Test statistic**:

$$
t = \frac{\bar{X} - \mu_0}{S / \sqrt{n}} \sim t_{n-1}
$$

**Rejection rules (level $\alpha$)**:

- Two-sided: reject $H_0$ if $|t| > t_{\alpha/2,\, n-1}$
- Right-tailed: reject if $t > t_{\alpha,\, n-1}$
- Left-tailed: reject if $t < -t_{\alpha,\, n-1}$

---

## 3. Population Proportion $p$

### 3.1 CI for $p$

- Data: $X \sim \text{Binomial}(n, p)$
- Sample proportion: $\hat{p} = X/n$

For large $n$:

$$
\hat{p} \approx N\left(p, \frac{p(1-p)}{n}\right)
$$

Approximate CI:

$$
\boxed{
p \in \hat{p} \pm z_{\alpha/2} \sqrt{\frac{\hat{p}(1 - \hat{p})}{n}}
}
$$

(Use when $n\hat{p}$ and $n(1-\hat{p})$ are “large enough”.)

---

### 3.2 Hypothesis Test for $p$

- Null: $H_0: p = p_0$
- Alternative:
  - $H_a: p \ne p_0$ (two-sided)
  - $H_a: p > p_0$ (right)
  - $H_a: p < p_0$ (left)

**Test statistic** (use $p_0$ in the standard error):

$$
z = \frac{\hat{p} - p_0}{\sqrt{\dfrac{p_0(1 - p_0)}{n}}}
$$

Compare $z$ to $z_{\alpha/2}$ or $z_\alpha$ just like the one-mean Z-test.

---

## 4. Two Means (Independent Samples)

Let:

- Sample 1: $\bar{x}_1$, $s_1$, $n_1$, population mean $\mu_1$
- Sample 2: $\bar{x}_2$, $s_2$, $n_2$, population mean $\mu_2$
- Parameter of interest: $\mu_1 - \mu_2$

Most tests use $(\mu_1 - \mu_2)_0 = 0$ under $H_0$, but keep it general.

---

### 4.1 Two Means, $\sigma_1$ and $\sigma_2$ Known (Z)

#### CI for $\mu_1 - \mu_2$

Given known $\sigma_1, \sigma_2$:

$$
\boxed{
(\mu_1 - \mu_2) \in 
(\bar{x}_1 - \bar{x}_2) \pm
z_{\alpha/2} \sqrt{\frac{\sigma_1^2}{n_1} + \frac{\sigma_2^2}{n_2}}
}
$$

#### Hypothesis Test

- Null: $H_0: \mu_1 - \mu_2 = (\mu_1 - \mu_2)_0$ (often 0)
- Alternative: $H_a$ can be two-sided, $>$, or $<$.

**Test statistic**:

$$
z = 
\frac{(\bar{X}_1 - \bar{X}_2) - (\mu_1 - \mu_2)_0}
{\sqrt{\dfrac{\sigma_1^2}{n_1} + \dfrac{\sigma_2^2}{n_2}}}
$$

Compare $z$ to normal critical values.

---

### 4.2 Two Means, Unknown $\sigma$’s – Unpooled (Welch t)

Use when the variances are **not assumed equal**.

#### CI for $\mu_1 - \mu_2$

Replace $\sigma_i$ by $s_i$:

$$
\boxed{
(\mu_1 - \mu_2) \in
(\bar{x}_1 - \bar{x}_2) \pm
t_{\alpha/2,\, \nu} \sqrt{\frac{s_1^2}{n_1} + \frac{s_2^2}{n_2}}
}
$$

where df $\nu$ is given approximately by Welch’s formula:

$$
\nu \approx
\frac{\left(\dfrac{s_1^2}{n_1} + \dfrac{s_2^2}{n_2}\right)^2}
{\dfrac{\left(\dfrac{s_1^2}{n_1}\right)^2}{n_1 - 1}
+
\dfrac{\left(\dfrac{s_2^2}{n_2}\right)^2}{n_2 - 1}}
$$

(Some courses also use $\nu = \min(n_1 - 1, n_2 - 1)$ as a conservative choice.)

#### Hypothesis Test (Unpooled t)

- Null: $H_0: \mu_1 - \mu_2 = (\mu_1 - \mu_2)_0$
- Test statistic:

  $$
  t =
  \frac{(\bar{X}_1 - \bar{X}_2) - (\mu_1 - \mu_2)_0}
  {\sqrt{\dfrac{s_1^2}{n_1} + \dfrac{s_2^2}{n_2}}}
  $$

- Use df $\nu$ as above, and compare to $t$ critical values.

---

### 4.3 Two Means, Unknown $\sigma$’s – Pooled t (Equal Variances)

Use when we **assume** population variances are equal: $\sigma_1^2 = \sigma_2^2$.

#### Pooled variance

$$
s_p^2 = 
\frac{(n_1 - 1)s_1^2 + (n_2 - 1)s_2^2}{n_1 + n_2 - 2}
$$

Standard error of $\bar{X}_1 - \bar{X}_2$:

$$
SE = s_p \sqrt{\frac{1}{n_1} + \frac{1}{n_2}}
$$

Degrees of freedom:

$$
\nu = n_1 + n_2 - 2
$$

#### CI for $\mu_1 - \mu_2$ (pooled)

$$
\boxed{
(\mu_1 - \mu_2) \in
(\bar{x}_1 - \bar{x}_2) \pm
t_{\alpha/2,\, n_1 + n_2 - 2} \cdot s_p \sqrt{\frac{1}{n_1} + \frac{1}{n_2}}
}
$$

#### Hypothesis Test (pooled t)

- Null: $H_0: \mu_1 - \mu_2 = (\mu_1 - \mu_2)_0$ (usually 0)

**Test statistic**:

$$
t =
\frac{(\bar{X}_1 - \bar{X}_2) - (\mu_1 - \mu_2)_0}
{s_p \sqrt{\dfrac{1}{n_1} + \dfrac{1}{n_2}}}
\sim t_{n_1 + n_2 - 2}
$$

Decision rules as usual with $t$ critical values.

---

> Side note: **Paired data (matched pairs)**  
> If samples are paired (before/after, twins, etc.), compute differences $D_i$ and do a **one-sample t** on the $D_i$ (mean of differences).

---

## 5. Two Proportions

Let:

- Sample 1: $X_1$ successes out of $n_1$, $\hat{p}_1 = X_1/n_1$, population proportion $p_1$
- Sample 2: $X_2$ successes out of $n_2$, $\hat{p}_2 = X_2/n_2$, population proportion $p_2$
- Parameter: $p_1 - p_2$

---

### 5.1 CI for $p_1 - p_2$

Approximate CI (large samples):

$$
\boxed{
(p_1 - p_2) \in
(\hat{p}_1 - \hat{p}_2) \pm
z_{\alpha/2} \sqrt{\frac{\hat{p}_1(1 - \hat{p}_1)}{n_1} + \frac{\hat{p}_2(1 - \hat{p}_2)}{n_2}}
}
$$

---

### 5.2 Hypothesis Test for $p_1 - p_2$

Usually:

- Null: $H_0: p_1 - p_2 = 0$ (i.e., $p_1 = p_2$)
- Alternative:
  - $H_a: p_1 - p_2 \ne 0$
  - $H_a: p_1 - p_2 > 0$
  - $H_a: p_1 - p_2 < 0$

Under $H_0: p_1 = p_2 = p$, use the **pooled** estimate:

$$
\hat{p} = \frac{X_1 + X_2}{n_1 + n_2}
$$

**Test statistic**:

$$
z =
\frac{(\hat{p}_1 - \hat{p}_2) - 0}
{\sqrt{\hat{p}(1 - \hat{p})\left(\dfrac{1}{n_1} + \dfrac{1}{n_2}\right)}}
$$

Compare $z$ to standard normal critical values.

---

## 6. One Variance / Standard Deviation

Let $X_1, \dots, X_n$ be a random sample from a **normal** population with variance $\sigma^2$.

- Sample variance:
  $$
  S^2 = \frac{1}{n-1} \sum_{i=1}^n (X_i - \bar{X})^2
  $$
- Key fact:
  $$
  \frac{(n-1)S^2}{\sigma^2} \sim \chi^2_{n-1}
  $$

---

### 6.1 CI for Variance $\sigma^2$

$100(1-\alpha)\%$ CI for $\sigma^2$:

$$
\boxed{
\sigma^2 \in
\left(
\frac{(n-1)s^2}{\chi^2_{\alpha/2,\, n-1}},
\;
\frac{(n-1)s^2}{\chi^2_{1-\alpha/2,\, n-1}}
\right)
}
$$

Then CI for $\sigma$ is just square roots of the endpoints.

---

### 6.2 Hypothesis Test for Variance $\sigma^2$

- Null: $H_0: \sigma^2 = \sigma_0^2$
- Alternative (one of):
  - $H_a: \sigma^2 > \sigma_0^2$
  - $H_a: \sigma^2 < \sigma_0^2$
  - $H_a: \sigma^2 \ne \sigma_0^2$

**Test statistic**:

$$
\chi^2 = \frac{(n-1)S^2}{\sigma_0^2} \sim \chi^2_{n-1}
$$

**Rejection regions (level $\alpha$)**:

- Right-tailed ($H_a: \sigma^2 > \sigma_0^2$):
  $$
  \text{Reject } H_0 \text{ if } \chi^2 > \chi^2_{\alpha,\, n-1}
  $$

- Left-tailed ($H_a: \sigma^2 < \sigma_0^2$):
  $$
  \text{Reject } H_0 \text{ if } \chi^2 < \chi^2_{1-\alpha,\, n-1}
  $$

- Two-sided ($H_a: \sigma^2 \ne \sigma_0^2$):
  $$
  \text{Reject } H_0 \text{ if }
  \chi^2 < \chi^2_{1-\alpha/2,\, n-1}
  \quad \text{or} \quad
  \chi^2 > \chi^2_{\alpha/2,\, n-1}
  $$

---

## 7. Tiny Summary (What to Use When)

| Situation                               | CI / Test Type                                |
|-----------------------------------------|-----------------------------------------------|
| 1 mean, $\sigma$ known                  | Z CI & Z test                                 |
| 1 mean, $\sigma$ unknown                | t CI & t test (df $= n-1$)                    |
| 1 proportion $p$                        | Z CI & Z test for $p$                         |
| 2 means, sigmas known                   | Two-sample Z                                  |
| 2 means, sigmas unknown, unequal var    | Two-sample **unpooled** t (Welch)             |
| 2 means, sigmas unknown, equal var      | Two-sample **pooled** t                       |
| 2 proportions                           | Two-sample Z for $p_1 - p_2$                  |
| 1 variance / SD                         | Chi-square CI & chi-square test for $\sigma^2$ |

---

*(Paste into Obsidian; inline math is `$...$`, block math is `$$...$$`.)*
