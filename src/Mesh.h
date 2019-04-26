#pragma once

#include <glm.hpp>
#include <ext.hpp>
#include <vector>

using glm::vec2;
using glm::vec3;
using glm::vec4;

class Mesh
{
public:
	// all member variables are set to 0, meaning the mesh is uninitialised
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual~Mesh();

	struct Vertex 
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	//pass the vertex information to the gpu to draw a mesh
	void initialise(unsigned int vertexCount,
					const Vertex* vertices,
					unsigned int indexCount = 0,
					unsigned int* indices = nullptr);

	// create a (1, 1, 1) cube mesh
	void initialiseCube();

	// cylinder can also  be used for prism by using less segments
	void initialiseCylinder(float radius, float length, unsigned int segments);

	//void initialisePyramid(float baseSides, float size);

	//create a small 2D square at global 0
	void initialiseQuad();

	virtual void draw();

protected:

	// the passed in vector is rotated by the given angle (radians)
	void rotate(vec2& vec, float angle);

	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};

