#include "Camera.h"
#include "MathUtils.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio) :
	m_fov{ fov },
	m_aspectRatio{ aspectRatio }
{
	LookAt(eye, target, up);
}

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	m_eye = eye;
	// set the camera axis vectors (forward, right, up)
	// forward vector (eye <- target)
	m_forward = glm::normalize(eye - target);//<make sure to normalize vector>
		// use cross product to create vectors
		// right = up x forward 
		m_right = glm::normalize(cross(up, m_forward)); //<make sure to normalize vector>
		// up = forward x right
		m_up = cross(m_forward, m_right); //< both vectors are normalized, no need to normalize : ) >

		CalculateViewPlane();
}

void Camera::CalculateViewPlane()
{
	// convert fov angle (degrees) to radians
	float theta = glm::radians(m_fov);

	// calculate the width / height of the view plane
	float halfHeight = tan(theta * 0.5f);
	float height = halfHeight * 2; //<twice the size of half height>;
	float width = m_aspectRatio * height; //<height * aspectRatio>;

	// calculate horizontal vector (right vector * width)
	m_horizontal = m_right * width;
		// calculate vertical vector (up vector * height)
		m_vertical = m_up * height;
		// calculate lower left location (origin)
		m_lowerLeft = m_eye - (m_horizontal * 0.5f) - (m_vertical * 0.5f) - m_forward;
}

ray_t Camera::GetRay(const glm::vec2& point) const
{
	ray_t ray;
	// The ray origin is the camera eye
	ray.origin = m_eye;
	// Calculate direction from point
	ray.direction = glm::normalize(m_lowerLeft + (m_horizontal * point.x) + (m_vertical * point.y) - m_eye);

	return ray;
}