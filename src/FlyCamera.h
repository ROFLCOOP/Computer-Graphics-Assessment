#pragma once
#include "Camera.h"
#include <glfw3.h>

using glm::vec2;

class FlyCamera : public Camera
{
public:
	FlyCamera(float fov, float aspectRatio, float nearF, float farF, vec3 from, vec3 to, vec3 up, float speed, GLFWwindow* window);
	~FlyCamera();

	void update(float dt) override;
	void setSpeed(float speed) { m_speed = speed; }

private:
	float m_speed = 1.0f;
	vec3 m_up;

	GLFWwindow* m_window;
	vec2 m_mousePos;
};

