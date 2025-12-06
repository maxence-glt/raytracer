https://oeis.org/wiki/List_of_LaTeX_mathematical_symbols

$\forall$ - for each / for every / for all
$\exists$ - there exists
$\therefore$ - therefore
$A \Longrightarrow B$ - whenever A is true, B is also true
$s.t.$ - such that
$\large\sum_{i=1}^{n}x_i = x_1 + x_2 + \cdot \cdot \cdot + x_n$
$\large \prod_{i=1}^{n}x_i = x_1 \times x_2 \times \cdot \cdot \cdot \times x_n$  
$\phi$ - empty set
$x^+$ - max(x, 0)
$N(\mu, \sigma^2)$ - normal distribution with mean $\mu$ and variance $\sigma^2$
##### Probability
$w$ - outcome of an experiment or trial
$\Omega$ - **Sample space**: the set of all possible outcomes
$P(w)$ - Probability of an outcome
**Event**: A set of outcomes and a subset of the sample space
$P(A)$: Probability of an event $A$, $P(A)=\sum_{w\in A}P(w)$
$A\cup B$ : Union, the set of outcomes in event A or B
$A\cap B$ or $AB$: Intersection, the set of outcomes in both $A$ and $B$
$A^c$: The complement of $A$, which is the event "not A"
**Mutually Exclusive**: $A\cap B=\phi$ 
**Random variable**: A **function** that maps each outcome ($w$) in the sample space ($\Omega$) into the set of real numbers

##### Combinatorial Analysis
*The mathematical theory of counting is often referred to as combinatorial analysis*

**Basic principle of counting**: Let $S$ be a set of length-$k$ sequences. If there are 
- $n_1$ possible first entries
- $n_2$ possible second entries for each first entry
- $n_3$ possible third entries for each combination of first and second entries, etc
Then there are a total of $n_1 \cdot n_2 \cdot\cdot\cdot n_k$ possible outcomes

**Permutation**: Rearrangement of objects into distinct sequences (order matters)
There are $\huge\frac{n!}{n_1!n_2!...n_r!}$ different permutations of $n$ objects, of which $n_1$ are alike, $n_2$ are alike, etc

**Combination**: An unordered collection of objects (order doesn't matter)
There are $\huge\binom{n}{k} = \frac{n!}{(n-k)!\, k!}$ different combinations of $n$ distinct objects taken $k$ at a time ([[binomial coefficient]])

**Binomial theorem**: $\huge (x + y)^n = \sum_{k=0}^{n}\binom{n}{k} x^k y^{n-k}$

**Inclusion-Exclusion Principle**: 5 and 6 in [[Probability Theorems]]
$$\left|\bigcup_{i=1}^{n} A_i\right|=\sum_{i=1}^{n}|A_i|-\sum_{1\le i<j\le n}|A_i\cap A_j|+\sum_{1\le i<j<k\le n}|A_i\cap A_j\cap A_k|-\cdots+(-1)^{n+1}|A_1\cap\cdots\cap A_n|$$

##### Conditional Probability and Bayes' formula
$P(A|B)$: if $P(B) > 0$ then $P(A|B)=\frac{P(AB)}{P(B)}$ is the fraction of B outcomes that are also A outcomes

**Multiplication Rule**: $P(E_1E_2\cdot\cdot\cdot E_n)=P(E_1)P(E_2|E_1)P(E_3|E_1E_2)\cdot\cdot\cdot P(E_n|E_1\cdot\cdot\cdot E_{n-1})$

**Law of total probability**: for any mutually exclusive events {$F_i$}, $i=1,2,\cdot\cdot\cdot, n$ whose union is the entire sample space we have 
$$ P(E)=P(EF_1)+P(EF_2)+\cdot\cdot\dot+P(EF_n)=\sum_{i=1}^{n}P(E|F_i)P(F_i)$$
**Independent events**: $P(EF) = P(E)P(F) \longrightarrow P(EF^C)=P(E)P(F^C)$

**Bayes' Formula**: [[Bayes' Theorem]]

**Expected Value, Variance, and Covariance**
if $E[X_i]$ is finite for all $i = 1, \cdot\cdot\cdot, n,$ then $E[X_i+\cdot\cdot\cdot X_n]=E[X_i]+\cdot\cdot\cdot+E[X_n]$. The relationship holds whether the $x_i$'s are independant of each other or not.

If $X$ and $Y$ are independant, then $E[g(X)h(Y)] = E[g(X)]E[h(Y)]$.

**Covariance**: $Cov(X,Y)=E[(X-E[X])(Y-E[Y])] = E[XY]-E[X]E[Y]$ 

**Correlation**: $\large \rho(X,Y)=\frac{Cob(X,Y)}{\sqrt{Var(X)Var(Y)}}$ 
If $X$ and $Y$ are independent, $Cov(X,Y)=0$ and $\rho(X,Y)=0$

**General rules of variance and covariance**

$$
\operatorname{Cov}\!\left(\sum_{i=1}^{n} a_i X_i,\; \sum_{j=1}^{m} b_j Y_j\right)
= \sum_{i=1}^{n}\sum_{j=1}^{m} a_i b_j\, \operatorname{Cov}(X_i, Y_j).
$$

$$
\operatorname{Var}\!\left(\sum_{i=1}^{n} X_i\right)
= \sum_{i=1}^{n} \operatorname{Var}(X_i)
\;+\; 2 \sum_{i<j} \operatorname{Cov}(X_i, X_j).
$$

**Conditional expectation**

**Discrete $X\mid Y=y$:**
$$
\mathbb{E}[g(X)\mid Y=y]
= \sum_{x} g(x)\, p_{X\mid Y}(x\mid y)
= \sum_{x} g(x)\, \Pr(X=x\mid Y=y).
$$

**Continuous $X\mid Y=y$:**
$$
\mathbb{E}[g(X)\mid Y=y]
= \int_{-\infty}^{\infty} g(x)\, f_{X\mid Y}(x\mid y)\, dx.
$$
**Law of total expectation**

$$
\mathbb{E}[X] = \mathbb{E}\!\left[\mathbb{E}[X\mid Y]\right]
=
\begin{cases}
\displaystyle \sum_{y} \mathbb{E}[X\mid Y=y]\, \Pr(Y=y), & \text{(discrete $Y$)}\\[1em]
\displaystyle \int_{-\infty}^{\infty} \mathbb{E}[X\mid Y=y]\, f_Y(y)\, dy, & \text{(continuous $Y$)}.
\end{cases}
$$
