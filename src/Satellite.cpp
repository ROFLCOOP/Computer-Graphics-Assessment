#include "Satellite.h"


Satellite::Satellite(mat4 transform, Planet* parent, float radius, float linearVelocity, float angularVelocity, vec4 colour) : Planet(transform, radius, colour), m_parent(parent), m_angularVelocity(angularVelocity), m_linearVelocity(linearVelocity)
{
}

Satellite::Satellite(vec3 position, Planet * parent, float radius, float linearVelocity, float angularVelocity, vec4 colour) : Planet(position, radius, colour), m_parent(parent), m_angularVelocity(angularVelocity), m_linearVelocity(linearVelocity)
{
}

Satellite::~Satellite()
{
}

void Satellite::update()
{
	m_transform = glm::rotate(m_transform, m_angularVelocity * 0.01f, vec3(0, 1, 0));
	m_transform[3] += m_transform[2] * (m_linearVelocity * 0.01f);
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