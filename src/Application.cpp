#include "Application.h"



Application::Application()
{
}


Application::~Application()
{
}

bool Application::startup()
{
	return true;
}

bool Application::update()
{
	bool exit = true;

	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
	return true;
}

void Application::draw()
{
}

void Application::shutdown()
{
}
