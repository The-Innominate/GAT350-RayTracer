#pragma once
#include <glm/glm.hpp>

template <typename T>
inline T lerp(const T& a, const T& b, float t) {
	//Linear interpolation
	//<return (1 - t) * a + t * b> Also known as "lerp"
	//lerp(a,b,t) = ((1 - t) * a) + (t * b);
	return (1.0f - t) * a + t * b;
}

inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
{
	//< https://nic-gamedev.blogspot.com/2011/11/using-vector-mathematics-cross-products.htmlLinks to an external site. ?
	//<return cross product>
	return glm::vec3(
		v1.y * v2.z - v1.z * v2.y, 
		v1.z * v2.x - v1.x * v2.z, 
		v1.x * v2.y - v1.y * v2.x
	);
}

inline float dot(const glm::vec3& v1, const glm::vec3& v2) {
	//<return dot product>
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n){
	//< https://registry.khronos.org/OpenGL-Refpages/gl4/html/reflect.xhtml>;
	//<return reflection vector>
	return v - 2.0f * dot(v, n) * n;
}