#include "Application.h"
#include "Texture.h"
#include <iostream>


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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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


	Gizmos::create(SHRT_MAX, SHRT_MAX, SHRT_MAX, SHRT_MAX);

	// Add code here

	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "../data/shaders/normalmap.vert");
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "../data/shaders/multilight.frag");

	if (m_normalMapShader.link() == false)
	{
		printf("Textured Shader Error: %s\n", m_texturedShader.getLastError());
		return false;
	}

	if (m_spearMesh.load("../data/soulspear/soulspear.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}
	
	m_spearTransform =
	{
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1
	};


	m_objTransform =
	{
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1
	};

	m_lightOne.diffuse =  { 0, 0, 3 };
	m_lightOne.specular = { 0, 0, 3 };
	m_lightTwo.diffuse =  { 2, 0, 0 };
	m_lightTwo.specular = { 2, 0, 0 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };

	//edit camera view here
	m_flyCam = new FlyCamera(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f, vec3(-25, 25, 25), vec3(0), vec3(0, 1, 0), 5, 1, m_window);

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	return true;
}

void Application::shutdown()
{
	Gizmos::destroy();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Application::update()
{
	m_curTime = glfwGetTime();
	m_deltaTime = m_curTime - m_prevTime;
	m_prevTime = m_curTime;
	
	float pos = glm::cos(m_curTime * 10);

	m_lightOne.direction = glm::normalize(vec3(-pos, 
											1, -1));
	m_lightTwo.direction = glm::normalize(vec3(pos,
											1, -1));
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::clear();


	//add code here

	Gizmos::addTransform(glm::mat4(1));



	m_flyCam->update(m_deltaTime);
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	if (!(glfwWindowShouldClose(m_window) == false && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS))
		return false;

	return true;
}

void Application::draw()
{
	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 99; i++)
	{
		Gizmos::addLine(vec3(-49 + i, 0, 49),
			vec3(-49 + i, 0, -49),
			i == 49 ? white : black);

		Gizmos::addLine(vec3(49, 0, -49 + i),
			vec3(-49, 0, -49 + i),
			i == 49 ? white : black);
	}

	// the following is for passing information to the shader
	m_normalMapShader.bind();
	m_normalMapShader.bindUniform("cameraFacing", vec3(m_flyCam->getWorldTransform()[2]));
	m_normalMapShader.bindUniform("dirLight1", m_lightOne.light);
	m_normalMapShader.bindUniform("dirLight2", m_lightTwo.light);
	m_normalMapShader.bindUniform("Ia", m_ambientLight);
	auto pvm = m_flyCam->getProjectionView() * m_spearTransform;
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm);
	m_normalMapShader.bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_spearTransform)));
	//

	m_spearMesh.draw();

	Gizmos::draw(m_flyCam->getProjectionView());

	glfwSwapBuffers(m_window);
	glfwPollEvents();

}

