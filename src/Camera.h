#pragma once
#include <glm.hpp>
#include <ext.hpp>

using glm::mat4;
using glm::vec3;
using glm::vec4;

class Camera
{
public:
	//Camera(mat4 worldTransform, mat4 viewTransform, mat4 projectionTransform, mat4 projectionViewTransform);
	Camera(float fov, float aspectRatio, float nearF, float farF, vec3 from, vec3 to, vec3 up);
	~Camera();

	virtual void update(float dt) = 0;
	virtual void setPerspective(float fov, float aspectRatio, float near, float far);
	virtual void setLookAt(vec3 from, vec3 to, vec3 up);
	virtual void setPosition(vec3 position);
	virtual mat4 getWorldTransform() { return m_worldTransform; }
	virtual mat4 getView() { return m_viewTransform; }
	virtual mat4 getProjection() { return m_projectionTransform; }
	virtual mat4 getProjectionView() { return m_projectionViewTransform; }

protected:
	mat4 m_worldTransform;
	mat4 m_viewTransform;
	mat4 m_projectionTransform;
	mat4 m_projectionViewTransform;

	virtual void updateProjectionViewTransform();
};

