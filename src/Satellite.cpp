#include "Satellite.h"
#include <iostream>


Satellite::Satellite(mat4 transform, Planet* parent, float radius, float linearVelocity, float angularVelocity, vec4 colour) : Planet(transform, radius, colour), m_parent(parent), m_angularVelocity(angularVelocity), m_linearVelocity(linearVelocity)
{
}

Satellite::Satellite(vec3 position, Planet * parent, float radius, float linearVelocity, float angularVelocity, vec4 colour) : Planet(position, radius, colour), m_parent(parent), m_angularVelocity(angularVelocity), m_linearVelocity(linearVelocity)
{
}

Satellite::~Satellite()
{
}

void Satellite::update(float dt)
{
	float scale = glm::pi<float>() * glm::distance(vec3(0), vec3(m_transform[3] * 2.0f)) * 0.16f;
	m_transform = glm::rotate(m_transform, glm::pi<float>() * 0.32f * dt, vec3(0, 1, 0));
	m_transform[3] += m_transform[2] * scale * dt;

	std::cout << "distance from planet: " << glm::distance(getMat()[3], m_parent->getTransform()[3]) << std::endl;
}

void Satellite::drawGizmo()
{
	mat4 temp = getMat();

	aie::Gizmos::addSphere(temp[3], m_radius, 10, 10, m_colour);
}

mat4 Satellite::getMat() const
{
	return m_parent->getTransform() * m_transform;
}
