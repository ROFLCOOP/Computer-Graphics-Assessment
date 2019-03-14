#include "Application.h"



Application::Application()
{
}


Application::~Application()
{
}

bool Application::startup(int windowWidth, int windowHeight)
{
	if (!glfwInit())
		return false;

	m_window = glfwCreateWindow(windowWidth, windowHeight, "Computer Graphics", nullptr, nullptr);

	if (m_window == nullptr)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return false;
	}


	Gizmos::create(65535U, 65535U, 65535U, 65535U);

	m_view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	m_projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);

	// Add code here
	Planet* sun = new Planet(vec3(0, 0, 0), 1, vec4(1.0f, 0.7f, 0.0f, 1.0f));
	Satellite* earth = new Satellite(vec3(-3, 0, 0), sun, 0.5f, 5.0f, glm::pi<float>() * 0.5f, vec4(0, 0, 1, 1));
	Satellite* moon = new Satellite(vec3(-0.75f, 0, 0), earth, 0.25f, 2.5f, glm::pi<float>(), vec4(1, 1, 1, 1));

	m_system.push_back(sun);
	m_system.push_back(earth);
	m_system.push_back(moon);
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	return true;
}

void Application::shutdown()
{
	Gizmos::destroy();
	for (Planet* obj : m_system)
	{
		delete obj;
	}
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Application::update(float dt)
{
	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::clear();

	//add code here

	Gizmos::addTransform(glm::mat4(1));



	for (Planet* planet : m_system)
	{
		planet->update();
	}
	
	for (Planet* planet : m_system)
	{
		planet->drawGizmo();
	}
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	if (!(glfwWindowShouldClose(m_window) == false && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS))
		return false;

	return true;
}

void Application::draw()
{
	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; i++)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	Gizmos::draw(m_projection * m_view);

	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

