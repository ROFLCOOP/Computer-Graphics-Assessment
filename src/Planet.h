#pragma once

#include <glm.hpp>
#include <ext.hpp>
#include <Gizmos.h>

using glm::mat4;
using glm::vec4;
using glm::vec3;

class Planet
{
public:
	Planet(mat4 transform, float radius, vec4 colour);
	Planet(vec3 position, float radius, vec4 colour);
	~Planet();

	virtual void update(float dt) {}
	virtual void drawGizmo();
	virtual mat4 getTransform() const { return m_transform; }

protected:
	mat4 m_transform;
	vec4 m_colour;
	float m_radius;
};

