"A of curve fitting using linear polynomials to construct new data points within the range of a discrete set of known data points."

The function  $f(x)=(1-x)a+xb$  defined over $[0,1]$ linearly interpolates between $a$ at $x=0$ and b at $x=1$.

```cpp
float lerp(float x, float a, float b) {
	return (1 - x) * a + x * b;
}
```

```cpp
float LinearPDF(float x, float a, float b) { 
	if (x < 0 || x > 1) return 0; 
	return 2 * lerp(x, a, b) / (a + b)
}
```

```cpp
float SampleLinear(float u, float a, float b) {     
	if (u == 0 && a == 0) return 0;     
	float x = u * (a + b) / (a + std::sqrt(lerp(u, a*a, b*b));     
	return std::min(x, OneMinusEpsilon); }
```

```cpp
float InvertLinearSample(float x, float a, float b) { 
	return x * (a * (2 - x) + b * x) / (a + b); 
}
```
