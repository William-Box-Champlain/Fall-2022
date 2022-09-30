#pragma once
#include "GL/glew.h"
#include <string>

class Shader
{
public:
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
	void use();
	void setFloat(std::string name, float value);
	void setInt(std::string name, int value);
private:
	Shader(const Shader& r) = delete;
	std::string readFile(const std::string& filePath);
	GLuint compileShader(const char* shaderSource, GLenum type);
	GLuint m_id;
};

