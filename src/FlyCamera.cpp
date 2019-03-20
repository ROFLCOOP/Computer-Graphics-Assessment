#include "FlyCamera.h"
#include <iostream>





FlyCamera::FlyCamera(float fov, float aspectRatio, float nearF, float farF, vec3 from, vec3 to, vec3 up, float speed, float sensitivity, GLFWwindow* window) : Camera(fov, aspectRatio, nearF, farF, from, to, up), m_up(up), m_speed(speed), m_sensitivity(sensitivity), m_window(window)
{
	m_up = up;
}

FlyCamera::~FlyCamera()
{
}


// at some point this function should centre the mouse in the middle of the
//window (as long as the window is clicked). On the first frame the window is
//clicked, the change in mouse pos should not be applied to the camera.
//Try prev/current style.
void FlyCamera::update(float dt)
{
	double xpos, ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos);
	vec2 mousePos(xpos, ypos);

	//camera is only moveable while pressing the left mouse button
	if (glfwGetMouseButton(m_window, 0) == GLFW_PRESS)
	{
		if (mousePos != m_mousePos)
		{
			vec2 dif(m_mousePos - mousePos);

			std::cout << glm::length(dif) << std::endl;
			if (dif.x != 0)
				m_worldTransform = glm::rotate(m_worldTransform, (glm::pi<float>() * 0.15f) * dif.x * dt * m_sensitivity, vec3(m_viewTransform[1]));
			if (dif.y != 0)
				m_worldTransform = glm::rotate(m_worldTransform, (glm::pi<float>() * 0.15f) * dif.y * dt * m_sensitivity, vec3(1, 0, 0));

			//if camera rotates pitch too far, it should stop so the player can't turn upside down
			if (glm::dot(vec3(m_worldTransform[1]), vec3(0, 1, 0)) < 0)
			{
				float scale = glm::dot(vec3(m_worldTransform[1]), vec3(0, 1, 0));
				float dir = glm::dot(vec3(m_worldTransform[1]), vec3(1, 0, 0));

				if (dir < 0)
				{
					m_worldTransform = glm::rotate(m_worldTransform, glm::pi<float>() * 0.5f * (scale), vec3(1, 0, 0));
				}
				else
				{
					m_worldTransform = glm::rotate(m_worldTransform, glm::pi<float>() * -0.5f * (scale), vec3(1, 0, 0));
				}
			}
		}
		float speedScale = 1;
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			speedScale = 3;

		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_worldTransform[3] += (m_worldTransform[2] * m_speed) * -dt * speedScale;
		}
		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_worldTransform[3] += (m_worldTransform[2] * m_speed) * dt * speedScale;
		}
		if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_worldTransform[3] += (m_worldTransform[0] * m_speed) * -dt * speedScale;
		}
		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_worldTransform[3] += (m_worldTransform[0] * m_speed) * dt * speedScale;
		}
		m_viewTransform = glm::inverse(m_worldTransform);
	}

	m_mousePos = mousePos;

	updateProjectionViewTransform();
	
}
