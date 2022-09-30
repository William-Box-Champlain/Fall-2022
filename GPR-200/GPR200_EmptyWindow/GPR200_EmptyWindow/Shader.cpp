#include "Shader.h"
#include <fstream>
#include <sstream>

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	std::string vertexShaderString = readFile(vertexShaderPath);
	GLuint vertexShader = compileShader(vertexShaderString.c_str(), GL_VERTEX_SHADER);

	std::string fragmentShaderString = readFile(fragmentShaderPath);
	GLuint fragmentShader = compileShader(fragmentShaderString.c_str(), GL_FRAGMENT_SHADER);

	//Create an empty shader program
	m_id = glCreateProgram();

	//Attach our shader objects
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);

	//Link program - will create an executable program with the attached shaders
	glLinkProgram(m_id);

	//Logging
	int success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success) {

		GLchar infoLog[512];
		glGetProgramInfoLog(m_id, 512, NULL, infoLog);
		printf("Failed to link shader program: %s", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(m_id);
}

void Shader::setFloat(std::string name, float value)
{
	glProgramUniform1f(m_id, glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setInt(std::string name, int value)
{
	glProgramUniform1i(m_id, glGetUniformLocation(m_id, name.c_str()), value);
}

std::string Shader::readFile(const std::string& filePath)
{
	std::ifstream fileStream;
	fileStream.open(filePath);
	if (!fileStream.is_open()) {
		printf("Failed to open file %s ", filePath.c_str());
	}
	std::stringstream stringStream;
	stringStream << fileStream.rdbuf();
	fileStream.close();
	return stringStream.str();
}

GLuint Shader::compileShader(const char* shaderSource, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	//Provides the source code to the object.
	glShaderSource(shader, 1, &shaderSource, NULL);
	//Compiles the shader source
	glCompileShader(shader);

	//Get result of last compile - either GL_TRUE or GL_FALSE
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		const char* shaderName = shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
		//Dump logs into a char array - 512 is an arbitrary length
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("Failed to compile %s shader: %s", shaderName, infoLog);
	}
	return shader;
}
