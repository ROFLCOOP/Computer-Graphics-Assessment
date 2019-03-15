#include "Camera.h"





Camera::Camera(float fov, float aspectRatio, float nearF, float farF, vec3 from, vec3 to, vec3 up) : m_worldTransform(1.0f)
{
	setPerspective(fov, aspectRatio, nearF, farF);
	setLookAt(from, to, up);
	m_worldTransform = glm::inverse(m_viewTransform);
}

Camera::~Camera()
{
}

void Camera::setPerspective(float fov, float aspectRatio, float near, float far)
{
	m_projectionTransform = glm::perspective(fov, aspectRatio, near, far);
}

void Camera::setLookAt(vec3 from, vec3 to, vec3 up)
{
	m_viewTransform = glm::lookAt(from, to, up);
}

void Camera::setPosition(vec3 position)
{
	m_worldTransform[3] = vec4(position, 1);
}

void Camera::updateProjectionViewTransform()
{
	m_viewTransform = glm::inverse(m_worldTransform);
	m_projectionViewTransform = m_projectionTransform * m_viewTransform  ;
}
