#pragma once
#include <gl_core_4_4.h>
#include <Gizmos.h>
#include <glm.hpp>
#include <ext.hpp>
#include <glfw3.h>
#include "Planet.h"
#include "Satellite.h"
#include <vector>

using aie::Gizmos;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Application
{
public:
	Application();
	~Application();
	
	virtual bool startup(int windowWidth, int windowHeight);
	virtual bool update(float dt);
	virtual void draw();
	virtual void shutdown();

protected:
	GLFWwindow* m_window;
	mat4 m_view;
	mat4 m_projection;

	std::vector<Planet*> m_system;
};

