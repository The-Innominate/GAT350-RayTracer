#pragma once
#include <stdlib.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

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

inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max)
{
	//<return random vector between min and max>
	return glm::vec3(
		random(min.x, max.x),
		random(min.y, max.y),
		random(min.z, max.z)
	);
}

inline glm::vec3 randomInUnitSphere()
{
	glm::vec3 v;
	// generate random vectors between -1 <-> +1, return vector if length is less than 1
	do
	{
		v = { random(-1, 1), random(-1, 1), random(-1, 1) }; //get random vector between(-1, -1, -1) and (1, 1, 1)
	} while (glm::length2(v) >= 1.0f);

		return v;
}