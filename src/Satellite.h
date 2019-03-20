#pragma once
#include "Planet.h"

class Satellite : public Planet
{
public:
	Satellite(mat4 transform, Planet* parent, float radius, float linearVelocity, float angularVelocity, vec4 colour);
	Satellite(vec3 position, Planet* parent, float radius, float linearVelocity, float angularVelocity, vec4 colour);
	~Satellite();

	void update(float dt) override;

	void drawGizmo() override;

	mat4 getMat() const;


private:
	Planet* m_parent;
	float m_linearVelocity;
	float m_angularVelocity;
};

