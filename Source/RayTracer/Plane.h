#pragma once
#include "Object.h"

class Plane : public Object
{
public:
	Plane() = default;
	Plane(const glm::vec3& center, const glm::vec3& normal, std::shared_ptr<Material> material) :
		//<call object constructor passing material>,
		Object(material),
		//<set center>,
		m_center{ center },
		//<set normal>
		m_normal{ normal }
	{
	}

	bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

private:
	//<center of the plane>
	glm::vec3 m_center{ 0 };
		//<normal of the plane>
	glm::vec3 m_normal{ 0 };
};