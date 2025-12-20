Given random variables X, Y, … , that are defined on the same probability space, the **multivariate** or **joint probability distribution** for X, Y, … is a probability distribution that gives the probability that each of X, Y, … falls in any particular range or discrete set of values specified for that variable. 

>In the case of only two random variables, this is called a **bivariate distribution**, but the concept generalizes to any number of random variables.

The joint probability distribution can be expressed in terms of a joint [[Cumulative Distribution Function]] and either in terms of a joint [[probability density function]] or joint [[probability mass function]]. These in turn can be used to find two other types of distributions: the **marginal distribution** and the **conditional probability distribution** (giving the probabilities for any subset of the variables conditional on particular values of the remaining variables). 

The function $f(x, y)$ is called the **joint probability mass function** if:
(a) 
$$
0 \le f(x, y) \le 1.
$$

(b)
$$
\sum_{(x,y)\in S} \sum f(x,y) = 1.
$$

(c)
$$
P\big( (X, Y) \in A \big) = \sum_{(x,y)\in A} \sum f(x,y),
$$

where $A$ is a subset of the space $S$.

For a Bivariate Distribution, X and Y are independent iff $f(x,y)=f_X(x)\cdot f_Y(y)$
### Marginal Distribution
The **marginal distribution** gives the probabilities for any one of the variables with no reference to any specific ranges of values for the other variables

**Definition 4.1–2.**  
Let $X$ and $Y$ have the joint probability mass function $f(x,y)$ with space $S$.

The probability mass function of $X$ alone, which is called the **marginal probability mass function of $X$**, is defined by

$$
f_X(x) = \sum_y f(x,y) = P(X = x), \qquad x \in S_X,
$$

where the summation is taken over all possible $y$ values for each given $x$ in the $x$-space $S_X$.  
That is, the summation is over all $(x,y)$ in $S$ with a given $x$ value.

Similarly, the **marginal probability mass function of $Y$** is defined by

$$
f_Y(y) = \sum_x f(x,y) = P(Y = y), \qquad y \in S_Y.
$$
### Independence of X and Y

$X$ and $Y$ are independent **if and only if**  
for every $x \in S_X$ and $y \in S_Y$,

$$
P[X = x, Y = y] = P[X = x] \, P[Y = y],
$$

i.e.,

$$
f_{XY}(x, y) = f_X(x) f_Y(y).
$$
