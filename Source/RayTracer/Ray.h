#pragma once
#include <glm/glm.hpp>

struct ray_t
{
	ray_t() = default;
	ray_t(const glm::vec3& origin, const glm::vec3& direction) :
		origin{ origin },
		direction{ direction }
	{}


		//<return point> GetPoint(float distance) const { <return point> }
		glm::vec3 GetPoint(float distance) const { return origin + (direction * distance); }
		glm::vec3 operator * (float distance) const { return GetPoint(distance); }

		glm::vec3 origin;
		glm::vec3 direction;
		/*<3d origin>
		<3d direction>*/
};

struct raycastHit_t
{
	// distance along the ray direction, from the origin to the hit point
	float distance = 0;

	// world point of raycast hit
	glm::vec3 point{ 0 };
	// surface normal of raycast hit
	glm::vec3 normal{ 0 };

	// material attached to hit object
	class Material* material{ nullptr };
};