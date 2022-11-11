#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	Vertex(const glm::vec3& position, const glm::vec3& color) 
		: position(position), color(color) {};
};

/// <summary>
/// Just holds a bunch of vertex + face (indices) data
/// </summary>
struct MeshData {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

/// <summary>
/// Holds OpenGL buffers, can be drawn
/// </summary>
class Mesh {
public:
	Mesh(MeshData* meshData);
	~Mesh();
	void draw(bool drawAsPoints);
private:
	GLuint mVAO, mVBO, mEBO;
	GLsizei mNumIndices;
	GLsizei mNumVertices;
};