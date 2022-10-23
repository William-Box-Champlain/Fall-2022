#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include <string>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"

void resizeFrameBufferCallback(GLFWwindow* window, int width, int height);
void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);

//automatically do the legwork to make textures
GLuint generateTexture(std::string inputTexture, GLint param = GL_LINEAR, GLint format = GL_RGB)
{
	//generate texture
	GLuint output;
	glGenTextures(1, &output);
	//bind texture to GL_TEXTURE_2D to make it into a 2D texture
	glBindTexture(GL_TEXTURE_2D, output);

	int width, height, numComponents;
	unsigned char* textureData = stbi_load(inputTexture.c_str(), &width, &height, &numComponents, 0);

	if (!textureData) printf("Failed to load file");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);


	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);

	return output;
}

//Full screen quad
const float backgroundVertexData[] = {
	//x      y      z	 r     g    b    a    s    t  
	-1.0,  -1.0,  0.0,  1.0, 1.0, 1.0, 1.0, 0.0, 0.0,	//bottom left
	 1.0,  -1.0,  0.0,  1.0, 1.0, 1.0, 1.0,	1.0, 0.0,	//bottom right
	 1.0,   1.0,  0.0,  1.0, 1.0, 1.0, 1.0,	1.0, 1.0,	//top right
	-1.0,   1.0,  0.0,  1.0, 1.0, 1.0, 1.0,	0.0, 1.0,	//top left
};

//Character quad
const float characterVertexData[] = {
	//x      y      z	 r     g    b    a    s    t  
	-0.5,  -0.5,  0.0,  1.0, 1.0, 1.0, 1.0, 0.0, 0.0,	//bottom left
	 0.5,  -0.5,  0.0,  1.0, 1.0, 1.0, 1.0,	1.0, 0.0,	//bottom right
	 0.5,   0.5,  0.0,  1.0, 1.0, 1.0, 1.0,	1.0, 1.0,	//top right
	-0.5,   0.5,  0.0,  1.0, 1.0, 1.0, 1.0,	0.0, 1.0,	//top left
};

const unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};

const std::string backgroundImage = "textures/background.jpg";
const std::string noiseImage = "textures/noise.jpg";
const std::string characterImage = "textures/Furby.png";

int main() {
	if (!glfwInit()) {
		printf("glfw failed to init");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Textures", 0, 0);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("glew failed to init");
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, resizeFrameBufferCallback);
	glfwSetKeyCallback(window, keyboardCallback);

	Shader backgroundShader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
	Shader characterShader("shaders/characterVertexShader.vert", "shaders/characterFragmentShader.frag");


	stbi_set_flip_vertically_on_load(true);

	GLuint backgroundTexture = generateTexture(backgroundImage);
	GLuint noiseTexture = generateTexture(noiseImage);
	GLuint characterTexture = generateTexture(characterImage, GL_NEAREST, GL_RGBA);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(backgroundVertexData), &backgroundVertexData, GL_STATIC_DRAW);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (const void*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (const void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	//UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (const void*)(sizeof(float) * 7));
	glEnableVertexAttribArray(2);

	//Enable back-face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float time = (float)glfwGetTime();

		backgroundShader.use();
		backgroundShader.setFloat("iTime", time);

		//set texture uniforms
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, backgroundTexture);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, noiseTexture);

		glActiveTexture(GL_TEXTURE0);

		backgroundShader.setInt("iTexture", 0);
		backgroundShader.setInt("iNoiseTexture", 1);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		characterShader.use();
		characterShader.setFloat("iTime", time);

		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, characterTexture);

		glActiveTexture(GL_TEXTURE0 + 2);

		characterShader.setInt("iTexture", 2);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void resizeFrameBufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
}
