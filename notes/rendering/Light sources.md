Without lighting, there would be little point in rendering a scene. A ray tracer must model the distribution of light throughout the scene, including not only the locations of the lights themselves but also the way in which they distribute their energy throughout space.

We frequently would like to know the amount of light power being deposited on the differential area surrounding the intersection point p.

> Point light sources have some power $\phi$ associated with it and that it radiates light equally in all directions
> Power per area on a unit sphere is $\phi / 4\pi$

![[Pasted image 20251018101101.png]]

> the power per area arriving at a point on a sphere of radius $r$ is proportional to $1/r^2$.

it can be shown that if the tiny surface patch dA is tilted by an angle $\theta$ away from the vector from the surface point to the light, the amount of power deposited on dA is proportional to $cos\theta$

> $\LARGE dE = \frac{\phi\cos\theta}{4\pi r^2}$