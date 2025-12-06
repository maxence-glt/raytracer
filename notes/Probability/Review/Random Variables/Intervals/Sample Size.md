
Goal: choose **sample size** $n$ so that a confidence interval has a desired **margin of error** $M$ at confidence level $1 - \alpha$.

All CI formulas have:

$$
\text{estimate} \;\pm\; (\text{critical value}) \times (\text{standard error})
$$

The **margin of error** is:

$$
M = (\text{critical value}) \times (\text{standard error})
$$

We solve for $n$ so that $M$ is no larger than a chosen target.

---

## 1. Sample Size for a CI for a Population Mean (σ Known)

### 1.1 CI formula (known σ)

For a population mean $\mu$ with known $\sigma$, the $(1-\alpha)$ CI is:

$$
\bar{X} \pm z_{\alpha/2} \cdot \frac{\sigma}{\sqrt{n}}
$$

So the margin of error is:

$$
M = z_{\alpha/2} \cdot \frac{\sigma}{\sqrt{n}}
$$

### 1.2 Solve for n

We want a margin of error no larger than a target $M$:

$$
z_{\alpha/2} \cdot \frac{\sigma}{\sqrt{n}} \le M
$$

Solve step by step:

1. Divide both sides by $z_{\alpha/2}$:
   $$
   \frac{\sigma}{\sqrt{n}} \le \frac{M}{z_{\alpha/2}}
   $$

2. Invert and square (everything positive):
   $$
   \sqrt{n} \ge \frac{z_{\alpha/2} \sigma}{M}
   $$

   $$
   n \ge \left( \frac{z_{\alpha/2} \sigma}{M} \right)^2
   $$

**Planning formula**:

$$
\boxed{
n = \left( \frac{z_{\alpha/2} \sigma}{M} \right)^2
}
$$

In practice, **always round up** to the next whole number:

- Compute $n_{\text{calc}}$ from the formula,
- Final sample size $n = \lceil n_{\text{calc}} \rceil$.

---

## 2. Sample Size for a CI for a Population Mean (σ Unknown)

When $\sigma$ is unknown, the exact CI uses **t**, but for planning $n$ we don’t know $s$ yet (since we don’t have the data). So we approximate.

### 2.1 CI formula (unknown σ)

For normal data with unknown $\sigma$:

$$
\bar{X} \pm t_{\alpha/2,\, n-1} \cdot \frac{S}{\sqrt{n}}
$$

Margin of error:

$$
M = t_{\alpha/2,\, n-1} \cdot \frac{S}{\sqrt{n}}
$$

Problem: $S$ and $t_{\alpha/2,\, n-1}$ both depend on the sample.

### 2.2 Typical planning approach (STAT 400 style)

To **plan** $n$ when $\sigma$ is unknown, one of these is usually done:

1. Use a **prior estimate** of $\sigma$, call it $\sigma^*$:
   - From a **previous study**,
   - From a **pilot sample**,
   - Or from a rough range rule (e.g., for roughly normal data, $\sigma \approx \text{range}/4$).

2. Replace $t_{\alpha/2,\, n-1}$ by $z_{\alpha/2}$ (since for moderate/large $n$, $t$ and $z$ are very close).

Then use the **same formula** as in the known-σ case, but plug in $\sigma^*$:

$$
\boxed{
n \approx \left( \frac{z_{\alpha/2} \, \sigma^*}{M} \right)^2
}
$$

Again, compute this $n_{\text{calc}}$ and **round up**:

$$
n = \lceil n_{\text{calc}} \rceil
$$

---

## 3. Sample Size for a CI for a Population Proportion $p$

### 3.1 CI formula for $p$

For a large sample, the $(1-\alpha)$ CI for the population proportion $p$ is:

$$
\hat{p} \pm z_{\alpha/2} \sqrt{\frac{\hat{p}(1 - \hat{p})}{n}}
$$

Margin of error:

$$
M = z_{\alpha/2} \sqrt{\frac{\hat{p}(1 - \hat{p})}{n}}
$$

Here $\hat{p}$ is the sample proportion of successes.

### 3.2 Using an anticipated proportion $p^*$

When planning $n$, we don’t know $\hat{p}$ yet, so we use a **guess** $p^*$:

- $p^*$ from previous data or a pilot study, **or**
- If no idea, use $p^* = 0.5$ (this gives the **largest** required $n$, “worst-case”).

Replace $\hat{p}$ by $p^*$ in the margin of error:

$$
M = z_{\alpha/2} \sqrt{\frac{p^*(1 - p^*)}{n}}
$$

We want:

$$
z_{\alpha/2} \sqrt{\frac{p^*(1 - p^*)}{n}} \le M
$$

Solve:

1. Divide:
   $$
   \sqrt{\frac{p^*(1 - p^*)}{n}} \le \frac{M}{z_{\alpha/2}}
   $$

2. Square:
   $$
   \frac{p^*(1 - p^*)}{n} \le \left( \frac{M}{z_{\alpha/2}} \right)^2
   $$

3. Solve for $n$:
   $$
   n \ge p^*(1 - p^*) \left( \frac{z_{\alpha/2}}{M} \right)^2
   $$

**Planning formula**:

$$
\boxed{
n = p^*(1 - p^*) \left( \frac{z_{\alpha/2}}{M} \right)^2
}
$$

Then **round up**:

$$
n = \lceil n_{\text{calc}} \rceil
$$

### 3.3 Worst-case sample size (no prior info)

The function $p^*(1 - p^*)$ is maximized at $p^* = 0.5$, with value $0.25$.

So if you want a conservative choice:

$$
p^* = 0.5 \quad \Rightarrow \quad p^*(1 - p^*) = 0.25
$$

Then

$$
n \ge 0.25 \left( \frac{z_{\alpha/2}}{M} \right)^2
$$

So a **worst-case planning formula** is:

$$
\boxed{
n = 0.25 \left( \frac{z_{\alpha/2}}{M} \right)^2
}
$$

(Again, round up.)

---

## 4. Quick Summary Table

Let $M$ be the desired margin of error, $z_{\alpha/2}$ the standard normal critical value, and $\sigma^*$ an estimate of $\sigma$ if needed.

| Quantity                  | CI Form (margin of error $M$)                                   | Sample Size Formula for planning                           |
|---------------------------|------------------------------------------------------------------|-----------------------------------------------------------|
| Mean, $\sigma$ known      | $M = z_{\alpha/2} \dfrac{\sigma}{\sqrt{n}}$                      | $n = \left( \dfrac{z_{\alpha/2} \sigma}{M} \right)^2$     |
| Mean, $\sigma$ unknown    | $M \approx z_{\alpha/2} \dfrac{\sigma^*}{\sqrt{n}}$              | $n \approx \left( \dfrac{z_{\alpha/2} \sigma^*}{M} \right)^2$ |
| Proportion $p$ (guess $p^*$) | $M \approx z_{\alpha/2} \sqrt{\dfrac{p^*(1-p^*)}{n}}$          | $n = p^*(1-p^*) \left( \dfrac{z_{\alpha/2}}{M} \right)^2$ |
| Proportion $p$ (worst-case)  | $M \approx z_{\alpha/2} \sqrt{\dfrac{0.25}{n}}$                | $n = 0.25 \left( \dfrac{z_{\alpha/2}}{M} \right)^2$       |

**Always:** after computing $n_{\text{calc}}$, take

$$
n = \lceil n_{\text{calc}} \rceil
$$

so your actual margin of error is at most $M$.
