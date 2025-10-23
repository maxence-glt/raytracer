Splitting increases the number of samples in some dimensions of multidimensional integrals in order to improve efficiency. As an example, consider an integral of the general form

$$\int_A \int_B f(x,y)dxdy$$

With the standard importance sampling estimator, we might $n$ draw samples from independent distributions, $X_i~ \textasciitilde ~p_x$and $Y_i~ \textasciitilde ~p_y$, and compute
$$\frac{1}{n}\sum_{i=1}^{n}\frac{f(X_i,Y_i)}{p_x(X_i)~p_y(Y_i)}$$

Splitting allows us to formalize the idea of taking more than one sample for the integral over $B$ for each sample taken in $A$. With splitting, we might take $m$ samples $Y_{i,j}$ for each sample $X_i$, giving the estimator
$$
\frac{1}{n}\sum_{i=1}^{n}\,\frac{1}{m}\sum_{j=1}^{m}
\frac{f\!\left(X_i, Y_{i,j}\right)}{p_x\!\left(X_i\right)\,p_y\!\left(Y_{i,j}\right)}.
$$
If it is possible to partially evaluate $f(X_i,~~)$ for each $X_i$, then we can compute a total of $nm$ samples more efficiently than we had taken $nm$ independent $X_i$ values using the standard importance sampling estimator.

##### Example
For an example from rendering, the original integral is evaluated to compute the color of pixels in an image:
- an integral is taken over the area of the pixel where at each point in the pixel $x$, a ray is traced into the scene and the reflected radiance at the intersection point is computed using an integral over the hemisphere (denoted here by$ B$) for which one or more rays are traced

With splitting, we can take multiple samples for each lighting integral, improving efficiency by amortizing the cost of tracing the initial ray from the camera over them.