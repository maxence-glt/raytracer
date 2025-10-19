- Written as $\xi$
- This variable takes on all values in its domain $[0, 1)$ independently and with uniform probability. 

This particular variable is important for two reasons:
1. Easy to generate a variable with this distribution in software—most runtime libraries have a pseudo-random number generator that does just that. 
2. We can take the canonical uniform random variable $\xi$ and map it to a discrete random variable, choosing $X$, if
   $\huge \sum_{j=1}^{i-1} p_j \le \xi < \sum_{j=1}^{i} p_j$

For lighting applications, we might want to define the probability of sampling illumination from each light in the scene based on its power relative to the total power from all sources:

> $\huge p_i = \frac{\overline{\Phi}_i}{\sum_j \Phi_j}\,.$

Notice that these $p$ values also sum to 1. Given such per-light probabilities, $\xi$ could be used to select a light source from which to sample illumination.

