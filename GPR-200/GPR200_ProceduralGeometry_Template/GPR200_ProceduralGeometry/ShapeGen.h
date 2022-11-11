#pragma once
#include "EW/Mesh.h"
#include <glm/gtc/type_ptr.hpp>

void createCube(float width, float height, float depth, glm::vec3 color, MeshData& meshData);
void createCone(float radius, float height, int numSegments, glm::vec3 color, MeshData& meshData);
void createSphere(float radius, int numSegments, glm::vec3 color, MeshData& meshData);
void createPlane(float width, float height, int subdivisions, glm::vec3 color, MeshData& meshData);

void createCube(float width, float height, float depth, glm::vec3 color, MeshData& meshData)
{
	meshData.vertices.clear();
	meshData.indices.clear();

	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	float halfDepth = depth / 2.0f;

	//VERTICES
	//-------------
	Vertex vertices[8] = {
		{glm::vec3(-halfWidth, -halfHeight, -halfDepth),color},
		{glm::vec3(-halfWidth, +halfHeight, -halfDepth),color},
		{glm::vec3(+halfWidth, +halfHeight, -halfDepth),color},
		{glm::vec3(+halfWidth, -halfHeight, -halfDepth),color},
		{glm::vec3(-halfWidth, -halfHeight, +halfDepth),color},
		{glm::vec3(-halfWidth, +halfHeight, +halfDepth),color},
		{glm::vec3(+halfWidth, +halfHeight, +halfDepth),color},
		{glm::vec3(+halfWidth, -halfHeight, +halfDepth),color}
	};
	meshData.vertices.assign(&vertices[0], &vertices[8]);

	//INDICES
	//-------------

	unsigned int indices[36] = {
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};
	meshData.indices.assign(&indices[0], &indices[36]);
}
