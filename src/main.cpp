#include <gl_core_4_4.h>
#include <Gizmos.h>
#include <glm.hpp>
#include <ext.hpp>
#include <glfw3.h>
#include "Planet.h"
#include "Satellite.h"

using aie::Gizmos;
using glm::vec3;
using glm::vec4;
using glm::mat4;

int main()
{
	if (glfwInit() == false)
		return -1;
	
	

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	//auto major = ogl_GetMajorVersion();
	//auto minor = ogl_GetMinorVersion();
	//printf("GL: %i.%i\n", major, minor);

	Gizmos::create(65535U, 65535U, 65535U, 65535U);

	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);

	Planet* sun = new Planet(vec3(0, 0, 0), 1, vec4(1.0f, 0.7f, 0.0f, 1.0f));
	Satellite* earth = new Satellite(vec3(-3, 0, 0), sun, 0.5f, 5.0f, glm::pi<float>() * 0.5f, vec4(0, 0, 1, 1));
	Satellite* moon = new Satellite(vec3(-0.75f, 0, 0), earth, 0.25f, 2.5f, glm::pi<float>(), vec4(1, 1, 1, 1));

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Gizmos::clear();

		Gizmos::addTransform(glm::mat4(1));
		// code go here
		vec4 white(1);
		vec4 black(0, 0, 0, 1);

		earth->update();
		moon->update();

		for (int i = 0; i < 21; i++)
		{
			Gizmos::addLine(vec3(-10 + i, 0, 10),
							vec3(-10 + i, 0, -10),
							i == 10 ? white : black);

			Gizmos::addLine(vec3(10, 0, -10 + i),
							vec3(-10, 0, -10 + i),
							i == 10 ? white : black);
		}
		
		sun->drawGizmo();
		earth->drawGizmo();
		moon->drawGizmo();

		Gizmos::draw(projection * view);

		//
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}