Bayes' theorem gives a mathematical rule for inverting conditional probabilities, allowing the probability of a cause to be found given its effect. 

Recall: If $P[A]>0$, then 
$$P(B_k~|~A)=\frac{P(B_k~\cap~A)}{P(A)}, \frac{P(B_k)P(A~|~B_k)}{P(A)}, ~k=1, 2, ..., m$$

Using the Law of Total Probability
$$P[A]~=~\sum_{i=1}^{m}P(B_i)P(A|B_i)$$
we have **Bayes Theorem**

$$P(B_k~|~A)=\frac{P(B_k)P(A~|~B_k)}{\sum_{i=1}^{m}P(B_i)P(A|B_i)}, k=1, 2, ..., m$$

For example:
> With Bayes' theorem, the probability that a patient has a disease given that they tested positive for that disease can be found using the probability that the test yields a positive result when the disease is present.

A more practical example:
> Bowl $B_1$ contains 2 red and 4 white chips
> Bowl $B_2$ contains 1 red and 2 white chips
> Bowl $B_3$ contains 5 red and 4 white chips
> The probabilities for selecting bowls is given by:
> $P(B_1)=1/3,\quad P(B_2)=1/6,\quad P(B_3)=1/2$
> 
> Q. What is the probability that a randomly drawn chip is **red** (from $B_1$, $B_2$, $B_3$)?
> $$P(R)=P(B_1~\cap~R)+P(B_2~\cap~R)+P(B_3\cap R)$$
> $$=P(B_1)P(R~|~B_1)+P(B_2)P(R~|~B_2)+P(B_3)P(R~|~B_3)$$
>  $$=\frac{1}{3}\cdot\frac{2}{6}+\frac{1}{6}\cdot\frac{1}{3}+\frac{1}{2}\cdot\frac{5}{9}=\frac{4}{9}$$
> $$P(B_1~|~R)=\frac{P(B_1~\cap~R)}{P(R)}=\frac{P(B_1)P(R~|~B_1)}{P(R)}=\frac{\frac{1}{3} \times \frac{2}{6}}{\frac{4}{9}} = \frac{1}{4}$$
>    $P(red~|~B_2)=\frac{1}{1~+~2} = \frac{1}{3}$
>    $P(red~|~B_3)=\frac{5}{5~+~4} = \frac{5}{9}$

