**Method Likelihood Estimation**

Choose the parameter value that makes the observed data **most likely**.

>**Likelihood function**
>$L(θ)=\prod_{i=1}^{n} f(x_i​​|θ)$
>
>and pick
>
>$θ_{MLE​}=argmax​_\theta L(θ)$

Typical MLE derivation steps
1. **Write down the joint [[Probability Density Function|PDF]] / [[Probability Mass Function|PMF]]** of the sample.
	- For multiple independent observations from the same distribution (iid), the [[Joint probability distribution|joint distribution]] is the product of the individual pdf/pmfs
2. Treat it as a function of $\theta$→ that’s your **likelihood**.
3. Take log: ℓ(θ)=ln⁡L(θ)
4. Differentiate w.r.t. θ, set derivative to 0.
5. Solve for θ, check it gives maximum (often obvious).

### Example 1 – MLE for $p$ in Bernoulli/Binomial

Assume $X_1, \dots, X_n \sim \text{Bernoulli}(p)$ i.i.d., where each $X_i \in \{0, 1\}$ and  
$\mathbb{P}(X_i = x_i) = p^{x_i}(1 - p)^{1 - x_i}$.

Let $S = \sum_{i=1}^n X_i$.

- Joint pmf (likelihood):  
  $L(p) = \prod_{i=1}^n p^{x_i}(1-p)^{1-x_i} = p^S (1-p)^{n-S}.$

- Log-likelihood:  
  $\ell(p) = \ln L(p) = S \ln p + (n - S)\ln(1-p).$

- Differentiate w.r.t. $p$:  
  $\dfrac{d\ell}{dp} = \dfrac{S}{p} - \dfrac{n-S}{1-p}.$

- Set derivative to 0 and solve:  
  $\dfrac{S}{p} = \dfrac{n-S}{1-p} \Rightarrow S(1-p) = p(n-S) \Rightarrow S = np \Rightarrow \hat{p} = \dfrac{S}{n}.$

So the MLE is  
$\hat{p}_{\text{MLE}} = \bar{X} = \dfrac{1}{n}\sum_{i=1}^n X_i.$

---
### Example 2 – MLE for $\lambda$ in Exponential$(\lambda)$

Assume $X_1, \dots, X_n \sim \text{Exponential}(\lambda)$ i.i.d. with pdf  
$f(x; \lambda) = \lambda e^{-\lambda x}$ for $x \ge 0$.

Let $T = \sum_{i=1}^n X_i$.

- Joint pdf (likelihood):  
  $L(\lambda) = \prod_{i=1}^n \lambda e^{-\lambda x_i} = \lambda^n e^{-\lambda T}.$

- Log-likelihood:  
  $\ell(\lambda) = \ln L(\lambda) = n \ln \lambda - \lambda T.$

- Differentiate w.r.t. $\lambda$:  
  $\dfrac{d\ell}{d\lambda} = \dfrac{n}{\lambda} - T.$

- Set derivative to 0 and solve:  
  $\dfrac{n}{\lambda} = T \Rightarrow \hat{\lambda} = \dfrac{n}{T} = \dfrac{1}{\bar{X}}.$

So the MLE is  
$\hat{\lambda}_{\text{MLE}} = \dfrac{1}{\bar{X}}.$