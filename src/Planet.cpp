#include "Planet.h"






Planet::Planet(mat4 transform, float radius, vec4 colour)
{
	m_transform = transform;
	m_radius = radius;
	m_colour = colour;
}

Planet::Planet(vec3 position, float radius, vec4 colour)
	: m_transform(1.0f)
{
	m_transform[3] = vec4(position, 1);
	m_radius = radius;
	m_colour = colour;
}

Planet::~Planet()
{
}

void Planet::drawGizmo()
{
	aie::Gizmos::addSphere(m_transform[3], m_radius, 10, 10, m_colour);
}

//void Planet::update()
//{
//	glm::rotate(m_transform, m_angularVelocity, vec3(0, 1, 0));
//	m_transform[3] += m_transform[0] * m_linearVelocity;
//}
