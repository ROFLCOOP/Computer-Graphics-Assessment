#pragma once
#include <gl_core_4_4.h>
#include <Gizmos.h>
#include <glm.hpp>
#include <ext.hpp>
#include <glfw3.h>
#include <vector>
#include "Planet.h"
#include "Satellite.h"
#include "FlyCamera.h"

#include <OBJMesh.h>

#include <Shader.h>
#include "Mesh.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/transform.hpp>

using aie::Gizmos;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::quat;

class Application
{
public:
	Application();
	~Application();
	
	virtual bool startup(int windowWidth, int windowHeight);
	virtual bool update();
	virtual void draw();
	virtual void shutdown();

protected:
	GLFWwindow* m_window;
	//mat4 m_view;
	//mat4 m_projection;

	vec3 m_positions[2];
	quat m_rotations[2];

	aie::ShaderProgram	m_texturedShader;
	aie::ShaderProgram	m_shader;
	aie::ShaderProgram	m_phongShader;
	aie::ShaderProgram	m_normalMapShader;

	Mesh				m_testMesh;
	mat4				m_objTransform;

	FlyCamera* m_flyCam;

	aie::Texture m_gridTexture;

	struct Light
	{
		union
		{
			struct
			{
				vec3	direction;
				vec3	diffuse;
				vec3	specular;
			};
			glm::mat3 light;
		};
	};
	Light		m_lightOne;
	Light		m_lightTwo;
	vec3		m_ambientLight;

	aie::OBJMesh m_spearMesh;
	mat4 m_spearTransform;
	//aie::OBJMesh	m_bunnyMesh;
	//mat4			m_bunnyTransform;

	float m_deltaTime = 0;
	double m_prevTime = 0;
	double m_curTime = 0;


};

