#include "Mesh.h"
#include <gl_core_4_4.h>
#include <iostream>

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialise(unsigned int vertexCount,
					const Vertex * vertices,
					unsigned int indexCount,
					unsigned int * indices)
{
	assert(vao == 0);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex),
		vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		triCount = indexCount / 3;
	}
	else
	{
		triCount = vertexCount / 3;
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::initialiseCube()
{
	//Vertex vertices[8];
	//vertices[0] = { glm::normalize(vec4(1, 1, 1, 1)), vec4(0,0,1,0), vec2(0,0) };
	//vertices[1] = { glm::normalize(vec4(1, -1, 1, 1)), vec4(0,0,1,0), vec2(0,0) };
	//vertices[2] = { glm::normalize(vec4(-1, -1, 1, 1)), vec4(0,0,1,0), vec2(0,0) };
	//vertices[3] = { glm::normalize(vec4(-1, 1, 1, 1)), vec4(0,0,1,0), vec2(0,0) };
	//vertices[4] = { glm::normalize(vec4(1, 1, -1, 1)), vec4(0,0,1,0), vec2(0,0) };
	//vertices[5] = { glm::normalize(vec4(1, -1, -1, 1)), vec4(0,0,1,0), vec2(0,0) };
	//vertices[6] = { glm::normalize(vec4(-1, -1, -1, 1)), vec4(0,0,1,0), vec2(0,0) };
	//vertices[7] = { glm::normalize(vec4(-1, 1, -1, 1)), vec4(0,0,1,0), vec2(0,0) };

	std::vector<Vertex> vertices;
	vertices.push_back({ glm::normalize(vec4(1, 1, 1, 1)), vec4(0,0,1,0), vec2(0,0) });
	vertices.push_back({ glm::normalize(vec4(1, -1, 1, 1)), vec4(0,0,1,0), vec2(0,0) });
	vertices.push_back({ glm::normalize(vec4(-1, -1, 1, 1)), vec4(0,0,1,0), vec2(0,0) });
	vertices.push_back({ glm::normalize(vec4(-1, 1, 1, 1)), vec4(0,0,1,0), vec2(0,0) });
	vertices.push_back({ glm::normalize(vec4(1, 1, -1, 1)), vec4(0,0,1,0), vec2(0,0) });
	vertices.push_back({ glm::normalize(vec4(1, -1, -1, 1)), vec4(0,0,1,0), vec2(0,0) });
	vertices.push_back({ glm::normalize(vec4(-1, -1, -1, 1)), vec4(0,0,1,0), vec2(0,0) });
	vertices.push_back({ glm::normalize(vec4(-1, 1, -1, 1)), vec4(0,0,1,0), vec2(0,0) });

	unsigned int indeces[36] =
	{
		0, 1, 2, 2, 3, 0,	// front
		4, 0, 1, 1, 5, 4,	// right
		3, 2, 6, 6, 7, 3,	// left
		4, 5, 6, 6, 7, 4,	// back
		0, 3, 7, 7, 4, 0,	// top
		1, 2, 6, 6, 5, 1	// bottom
	};

	initialise(8, &vertices[0], 36, &indeces[0]);
}

void Mesh::initialiseCylinder(float radius, float length, unsigned int segments)
{
	unsigned int totalVerts = segments * 2 + 2;
	std::vector<Vertex> vertices;

	// add the two end center verts (center of circle on each side)
	vertices.push_back({ vec4(0, 0, length * 0.5f, 0), vec4(0, 1, 0, 0), vec2(0,0) });
	vertices.push_back({ vec4(0, 0, -(length * 0.5f), 0), vec4(0, 1, 0, 0), vec2(0,0) });

	// add vetices to each side based on a directional vector that changes every iteration
	vec2 dir = vec2(0, 1);
	float angle = (glm::pi<float>() * 2) / segments;
	for (int i = 0; i < segments; i++)
	{
		dir = glm::normalize(dir);
		Vertex fore;
		Vertex back;
		fore.position = vec4((dir * radius), length * 0.5f, 1);
		back.position = vec4((dir * radius), -length * 0.5f, 1);
		vertices.push_back(fore);
		vertices.push_back(back);
		//vertices.push_back({vec4((dir * radius), length * 0.5f, 1), vec4(0, 1, 0, 0), vec2(0,0)});
		//vertices.push_back({vec4((dir * radius), -length * 0.5f, 1), vec4(0, 1, 0, 0), vec2(0,0)});
		rotate(dir, (glm::pi<float>() * 2) / segments);
	}

	std::vector<unsigned int> indeces;
	//the following loop populates the index list, focusing on a vertex from each end of the cylinder every iteration
	for (int i = 2; i < totalVerts; i+=2)
	{
		if (i + 2 == totalVerts) // if the for loop is at the end, it needs to use the first few verts again
		{
			indeces.push_back(i);
			indeces.push_back(0);
			indeces.push_back(2);
			indeces.push_back(i + 1);
			indeces.push_back(1);
			indeces.push_back(3);

			indeces.push_back(i);
			indeces.push_back(i + 1);
			indeces.push_back(2);
			indeces.push_back(i + 1);
			indeces.push_back(3);
			indeces.push_back(2);
		}
		else // the loop is structured this way because of the order in which the vert vector was populated
		{
			indeces.push_back(i);
			indeces.push_back(0);
			indeces.push_back(i + 2);
			indeces.push_back(i + 1);
			indeces.push_back(1);
			indeces.push_back(i + 3);

			indeces.push_back(i);
			indeces.push_back(i + 1);
			indeces.push_back(i + 2);
			indeces.push_back(i + 1);
			indeces.push_back(i + 3);
			indeces.push_back(i + 2);
		}
	}
	initialise(vertices.size(), &vertices[0], indeces.size(), &indeces[0]);
}

void Mesh::initialiseQuad()
{
	assert(vao == 0);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };

	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	vertices[0].texCoord = { 0, 1 }; // bottom left
	vertices[1].texCoord = { 1, 1 }; // bottom right
	vertices[2].texCoord = { 0, 0 }; // top left

	vertices[3].texCoord = { 0, 0 }; // top left
	vertices[4].texCoord = { 1, 1 }; // bottom right
	vertices[5].texCoord = { 1, 0 }; // top right

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	triCount = 2;
}

void Mesh::draw()
{
	glBindVertexArray(vao);

	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}

void Mesh::rotate(vec2& vec, float angle)
{
	if (angle == 0) return;

	float cs = cos(angle);
	float sn = sin(angle);
	float x = vec.x;
	float y = vec.y;

	vec.x = x * cs - y * sn;
	vec.y = x * sn + y * cs;
}
