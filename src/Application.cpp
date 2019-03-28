#include "Application.h"
#include "Texture.h"



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

	//m_shader.loadShader(aie::eShaderStage::VERTEX, "../data/shaders/simple.vert");
	//m_shader.loadShader(aie::eShaderStage::FRAGMENT, "../data/shaders/simple.frag");

	//if (m_shader.link() == false)
	//	printf("Shader Error: %s/n", m_shader.getLastError());

	//m_texturedShader.loadShader(aie::eShaderStage::VERTEX, "../data/shaders/textured.vert");
	//m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT, "../data/shaders/textured.frag");
	
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "../data/shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "../data/shaders/phong.frag");

	if (m_phongShader.link() == false)
	{
		printf("phong shader error: %s\n", m_phongShader.getLastError());
	}

	//if (m_texturedShader.link() == false)
	//{
	//	printf("Textured Shader Error: %s/n", m_texturedShader.getLastError());
	//	return false;
	//}

	if (m_spearMesh.load("../data/stanford/dragon.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}
	//if (m_gridTexture.load("../data/textures/numbered_grid.tga") == false)
	//{
	//	printf("Failed to load texture!\n");
	//	return false;
	//}
	m_spearTransform =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	//m_testMesh.initialiseQuad();
	//m_testMesh.initialiseCube();
	//m_testMesh.initialiseCylinder(2, 5, 10);

	m_objTransform =
	{
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1
	};

	m_light.diffuse = { 1, 1, 0 };
	m_light.specular = { 1, 1, 0 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };

	//edit camera view here
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
	
	m_light.direction = glm::normalize(vec3(glm::cos(m_curTime * 2), 
											glm::sin(m_curTime * 2), 0));

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
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

	//m_shader.bind();
	//m_texturedShader.bind();
	m_phongShader.bind();

	m_phongShader.bindUniform("cameraPosition", m_flyCam->getPosition());

	m_phongShader.bindUniform("Ia", m_ambientLight);
	m_phongShader.bindUniform("Id", m_light.diffuse);
	m_phongShader.bindUniform("Is", m_light.specular);
	m_phongShader.bindUniform("LightDirection", m_light.direction);


	auto pvm = m_flyCam->getProjectionView()/*;//*/ * m_spearTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	m_phongShader.bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_spearTransform)));
	//m_texturedShader.bindUniform("ProjectionViewModel", pvm);

	//assert(m_texturedShader.bindUniform("diffuseTexture", 0));

	//m_gridTexture.bind(0);


	m_spearMesh.draw();
	//m_testMesh.draw();

	//m_bunnyMesh.draw();

	Gizmos::draw(m_flyCam->getProjectionView());

	glfwSwapBuffers(m_window);
	glfwPollEvents();

}

