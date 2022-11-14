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

void createCone(float radius, float height, int numSegments, glm::vec3 color, MeshData& meshData)
{
	meshData.vertices.clear();
	meshData.indices.clear();

	//Generate Verts
	float topY = height;
	float bottomY = 0;
	float x, z;

	float thetaStep = (2 * glm::pi<float>()) / numSegments;

	for (int i = 0; i < numSegments; i++)
	{
		x = glm::cos(i * thetaStep) * radius;
		z = glm::sin(i * thetaStep) * radius;

		Vertex temp = Vertex(glm::vec3(x, bottomY, z), color);

		meshData.vertices.push_back(temp);
	}

	Vertex bottomCenter = Vertex(glm::vec3(0, bottomY, 0), color);
	meshData.vertices.push_back(bottomCenter);
	Vertex topCenter = Vertex(glm::vec3(0, topY, 0), color);
	meshData.vertices.push_back(topCenter);

	//Generate indices
	for (int i = 0; i < numSegments; i++)
	{
		int centerBottomIndex = numSegments;
		int centerTopIndex = numSegments+1;
		//Generate bottom indices
		meshData.indices.push_back(centerBottomIndex);
		meshData.indices.push_back(i);
		meshData.indices.push_back(((i + 1) % numSegments));

		//Generate side indices
		meshData.indices.push_back(centerTopIndex);
		meshData.indices.push_back(((i + 1) % numSegments));
		meshData.indices.push_back(i);
	}
}

void createSphere(float radius, int numSegments, glm::vec3 color, MeshData& meshData)
{
	//vertex data generation

	meshData.vertices.clear();
	meshData.indices.clear();

	float thetaStep = (2 * glm::pi<float>()) / numSegments;
	float phiStep = glm::pi<float>() / numSegments;

	int vertexCount = 0;

	Vertex temp = Vertex(glm::vec3(0.0f, radius, 0.0f), color);
	vertexCount++;

	meshData.vertices.push_back(temp);

	for (int i = 1; i < numSegments; i++)
	{
		float phi = i * phiStep;

		for (int j = 0; j <= numSegments; j++)
		{
			float theta = j * thetaStep;

			float x = radius * glm::sin(phi) * glm::sin(theta);
			float y = radius * glm::cos(phi);
			float z = radius * glm::sin(phi) * glm::cos(theta);

			temp = Vertex(glm::vec3(x, y, z), color);
			meshData.vertices.push_back(temp);
			vertexCount++;
		}
	}

	temp = Vertex(glm::vec3(0, -radius, 0), color);
	meshData.vertices.push_back(temp);
 	vertexCount++;

	//indicies generation

	int start = 1;
	int ringVertexCount = numSegments + 1;

	//sides
	for (int i = 0; i < numSegments - 2; i++)
	{
		for (int j = 0; j < numSegments; j++)
		{
			meshData.indices.push_back(start + i * ringVertexCount + j);
			meshData.indices.push_back(start + (i + 1) *ringVertexCount + j);
			meshData.indices.push_back(start + i * ringVertexCount + j + 1);
			meshData.indices.push_back(start + i * ringVertexCount + j + 1);
			meshData.indices.push_back(start + (i + 1) * ringVertexCount + j);
			meshData.indices.push_back(start + (i + 1) * ringVertexCount + j + 1);
		}
	}

	//top cap
	for (int i = 0; i < numSegments; i++)
	{
		meshData.indices.push_back(0);
		meshData.indices.push_back(i + 1);
		meshData.indices.push_back(i + 2);
	}
	//bottom cap
	int bottomInt = meshData.vertices.size() - 1;
	int bottomStart = bottomInt - ringVertexCount;
	for (int i = bottomStart; i < bottomInt; i++)
	{
		meshData.indices.push_back(bottomInt);
		meshData.indices.push_back(i + 1);
		meshData.indices.push_back(i);
	}
}

void createPlane(float width, float height, int subdivisions, glm::vec3 color, MeshData& meshData)
{
	meshData.vertices.clear();
	meshData.indices.clear();

	int columnSides = subdivisions + 1;

	for (int row = 0; row < columnSides; row++)
	{
		for (int column = 0; column < columnSides; column++)
		{
			float x = width / subdivisions * column;
			float y = height /subdivisions * row;

			Vertex temp = Vertex(glm::vec3(x, y, 0), color);

			meshData.vertices.push_back(temp);
		}
	}
	for (int row = 0; row < subdivisions; row++)
	{
		for (int column = 0; column < subdivisions; column++)
		{
			int start = row * columnSides + column;
			int right = start + 1;
			int topLeft = start + columnSides;
			int topRight = start + columnSides + 1;

			//first triangle
			meshData.indices.push_back(start);
			meshData.indices.push_back(right);
			meshData.indices.push_back(topRight);

			//second triangle
			meshData.indices.push_back(start);
			meshData.indices.push_back(topRight);
			meshData.indices.push_back(topLeft);
		}
	}
}