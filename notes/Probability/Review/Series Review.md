### Taylor Series

A Taylor series is a special case of a power series that provides a useful way to represent well-known functions.

For any function $f(x)$, the Taylor series of $f(x)$ at $a$ is

$$
f(x) = f(a) + (x-a) f'(a) + \frac{(x-a)^2}{2!} f''(a)
      + \cdots + \frac{(x-a)^n}{n!} f^{(n)}(a) + \cdots .
$$

Or, more compactly,

$$
f(x) = \sum_{n=0}^{\infty} \frac{(x-a)^n}{n!}\, f^{(n)}(a).
$$

A Maclaurin series is a Taylor series with $a = 0$.

---

### Geometric Series

Provided $|x| < 1$,

$$
\frac{1}{1 - x} = 1 + x + x^2 + x^3 + \cdots .
$$

Or, more compactly,

$$
\sum_{k=0}^{\infty} x^k = \frac{1}{1 - x}.
$$

We could also start from an arbitrary index:

$$
\sum_{k=m}^{\infty} x^k = \frac{x^m}{1 - x}.
$$

---

### Exponential Function

$$
e^x = 1 + x + \frac{x^2}{2!} + \frac{x^3}{3!} + \cdots .
$$

Or, more compactly,

$$
\sum_{k=0}^{\infty} \frac{x^k}{k!} = e^x.
$$

---

### Binomial Expansion

$$
(a + b)^n = \sum_{k=0}^{n} \binom{n}{k} a^{\,n-k} b^k.
$$

---

### Sum of Power of Integers

For the sum of the first $n$ integers:

$$
\sum_{k=1}^{n} k = \frac{n(n+1)}{2}.
$$

For the sum of the squares of the first $n$ integers:

$$
\sum_{k=1}^{n} k^2 = \frac{n(n+1)(2n+1)}{6}.
$$
