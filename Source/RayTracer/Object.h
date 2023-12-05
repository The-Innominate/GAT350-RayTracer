#pragma once
#include "Material.h"
#include "Ray.h"
#include <memory>


class Object
{
public:
	Object() = default;
	Object(std::shared_ptr<Material> material) :
		m_material{ material } {}

	virtual bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) = 0; //< make pure virtual > ;

	Material* GetMaterial() { return /*<get the raw pointer of the m_material>;*/ m_material.get();}

protected:
	std::shared_ptr<Material> m_material;
};