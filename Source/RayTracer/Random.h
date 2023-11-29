#pragma once
#include <stdlib.h>
#include <algorithm>

inline void seedRandom(unsigned int seed)
{
	//<use https ://cplusplus.com/reference/cstdlib/srand/Links to an external site.>
	srand(seed);
}

inline float random01()
{
	//<use https ://cplusplus.com/reference/cstdlib/rand/Links to an external site. (divide by RAND_MAX use floating - point divide)>
	return rand() / (float)RAND_MAX;
}

inline float random(float min, float max)
{
	//<if (min > max) swap values https ://cplusplus.com/reference/algorithm/swap/Links to an external site.>return <number between min and max>
	if (min > max) {
		std::swap(min, max);
	}
	return min + (max - min) * random01();
}