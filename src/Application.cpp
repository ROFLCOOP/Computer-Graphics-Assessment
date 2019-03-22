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


	Gizmos::create(65535U, 65535U, 65535U, 65535U);

	// Add code here

	m_shader.loadShader(aie::eShaderStage::VERTEX, "../data/shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "../data/shaders/colour.frag");

	if (m_shader.link() == false)
		printf("Shader Error: %s/n", m_shader.getLastError());

	m_texturedShader.loadShader(aie::eShaderStage::VERTEX, "../data/shaders/textured.vert");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT, "../data/shaders/textured.frag");
	
	if (m_texturedShader.link() == false)
		printf("Textured Shader Error: %s/n", m_texturedShader.getLastError());

	if (m_gridTexture.load("../data/textures/numbered_grid.tga") == false)
	{
		printf("Failed to load texture!\n");
		return false;
	}

	m_testMesh.initialiseCylinder(2, 8, 5);
	//m_testMesh.initialiseCube();

	m_quadTransform =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	m_positions[0] = vec3(10, 5, 10);
	m_positions[1] = vec3(-10, 0, -10);
	m_rotations[0] = quat(vec3(0, -1, 0));
	m_rotations[1] = quat(vec3(0, 1, 0));
	//
	

	//if (m_bunnyMesh.load("../data/stanford/bunny.obj") == false)
	//{
	//	printf("Bunny Mesh Error!\n");
	//	return false;
	//}
	//
	//m_bunnyTransform =
	//{
	//	0.5f,0,0,0,
	//	0,0.5f,0,0,
	//	0,0,0.5f,0,
	//	0,0,0,1
	//};


	//edit camera view here
	//m_view = glm::lookAt(vec3(0, 10, 0), vec3(0), vec3(0, 1, 0));
	//m_projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);
	m_flyCam = new FlyCamera(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f, vec3(-25, 25, 25), vec3(0), vec3(0, 1, 0), 5, 1, m_window);

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

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::clear();


	//add code here

	//float s = glm::cos(glfwGetTime()) * 0.5f + 0.5f;
	//
	//vec3 p = (1.0f - s) * m_positions[0] + s * m_positions[1];
	//
	//quat r = glm::slerp(m_rotations[0], m_rotations[1], s);
	//
	//mat4 m = glm::translate(p) * glm::toMat4(r);

	

	//Gizmos::addTransform(m);
	//Gizmos::addAABBFilled(p, vec3(0.5f), vec4(1, 0, 0, 1), &m);

	//m_view[3] += inverted[2] * dt;

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

	m_shader.bind();
	//m_texturedShader.bind();

	auto pvm = m_flyCam->getProjectionView()/*;//*/ * m_quadTransform;

	m_shader.bindUniform("ProjectionViewModel", pvm);

	//assert(m_texturedShader.bindUniform("diffuseTexture", 0));

	//m_gridTexture.bind(0);

	m_testMesh.draw();

	//m_bunnyMesh.draw();

	Gizmos::draw(m_flyCam->getProjectionView());

	glfwSwapBuffers(m_window);
	glfwPollEvents();

}

