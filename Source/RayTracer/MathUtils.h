#pragma once

template <typename T>
inline T lerp(const T a, const T b, float t) {
	//Linear interpolation
	//<return (1 - t) * a + t * b> Also known as "lerp"
	lerp(a,b,t) = ((1 - t) * a) + (t * b);
}