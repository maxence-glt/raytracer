The **degrees of freedom** is the number of values in the final calculation of a statistic or parameter that are free to vary

- Sample mean
  $$
  \bar{X} = \frac{1}{n} \sum_{i=1}^n X_i
  $$
- Sample variance
  $$
  S^2 = \frac{1}{n-1}\sum_{i=1}^n (X_i - \bar{X})^2
  $$
Core results:

1. **Standardized mean (σ known)**
   $$
   Z = \frac{\bar{X} - \mu}{\sigma / \sqrt{n}} \sim \mathcal{N}(0,1)
   $$

2. **Sample variance / chi-square**
   $$
   \frac{(n-1)S^2}{\sigma^2} \sim \chi^2_{n-1}
   $$

3. **Standardized mean (σ unknown) / t**
   $$
   T = \frac{\bar{X} - \mu}{S / \sqrt{n}} \sim t_{n-1}
   $$
Interpretation:

- Use **Z** when σ is **known** or \(n\) is large (CLT).
- Use **t** for the **mean** when σ is **unknown** and data ≈ normal.
- Use **chi-square** for **variance** and **categorical** tests.
