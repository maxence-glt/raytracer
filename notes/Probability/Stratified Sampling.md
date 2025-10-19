A technique for variance reduction based on the careful placement of samples in order to better capture the features of the integrand (or, more accurately, to be less likely to miss important features).

Stratified sampling decomposes the integration domain into regions and places samples in each one.

Stratified sampling subdivides the integration domain $\Lambda$ into $n$ nonoverlapping regions $\Lambda_1, \Lambda_2, ..., \Lambda_n$. Each region is called a _stratum_, and they must completely cover the original domain:

$\huge\bigcup\limits^n_{i=1}\Lambda_i=\Lambda$

To draw samples from $\Lambda$, we will draw $n_i$ samples from each $\Lambda_i$, according to densities $p_i$ inside each stratum. 
- A simple example is **_supersampling_** a pixel. With stratified sampling, the area around a pixel is divided into a grid $k \times k$, and a sample is drawn uniformly within each grid cell. This is better than taking $k^2$ random samples, since the sample locations are less likely to clump together.

##### Why does this technique reduce variance?
Within a single stratum $\Lambda_i$, the [[Monte Carlo Integration|monte carlo]] estimate is





