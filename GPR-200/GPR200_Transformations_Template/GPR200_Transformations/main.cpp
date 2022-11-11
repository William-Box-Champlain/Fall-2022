#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "camera.h"
#include "Transformations.h"

//#include <glm/glm.hpp>
//#include <glm/matrix.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <random>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"

glm::vec3 worldUp = glm::vec3(0, 1, 0);

const int TRANSFORM_COUNT = 5;

bool usePerspective = true;

transform boxTransform[TRANSFORM_COUNT];
camera sceneCamera;

glm::mat4 perspectiveMatrix;
glm::mat4 orthoMatrix;

void processInput(GLFWwindow* window);
void resizeFrameBufferCallback(GLFWwindow* window, int width, int height);
void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

GLuint loadTexture(const char* filePath);

float cubeVertexData[] = {
	//Back
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	//Front
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//Left
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 //Right
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 //Bottom
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//Top
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,
	 -0.5f, 0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
};

float prevTime;
float deltaTime;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1280;

const float DEFAULT_FOV = 90;
const float NEAR_PLANE = 0.1;
const float FAR_PLANE = 100;

projectionMatrix projection = projectionMatrix(DEFAULT_FOV, NEAR_PLANE, FAR_PLANE, SCREEN_WIDTH, SCREEN_HEIGHT);

int main() {
	if (!glfwInit()) {
		printf("glfw failed to init");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Transformations", 0, 0);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("glew failed to init");
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, resizeFrameBufferCallback);
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");

	GLuint texture = loadTexture("textures/Face.png");
	
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexData), &cubeVertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	
	//Enable back-face culling
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);
	//Only render if closer to camera
	glDepthFunc(GL_LESS);

	//set random transforms for boxes

	float min =-2.5;
	float max = 2.5;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(min, max);

	for (int i = 0; i < TRANSFORM_COUNT; i++)
	{
		float scalar = (float)dist(gen);

		float xRotation = (float)dist(gen);
		float yRotation = (float)dist(gen);
		float zRotation = (float)dist(gen);

		float xTranslation = (float)dist(gen);
		float yTranslation = (float)dist(gen);
		float zTranslation = (float)dist(gen);

		glm::vec3 randomScale = glm::vec3(scalar);
		glm::vec3 randomRotation = glm::vec3(xRotation,yRotation,zRotation);
		glm::vec3 randomTranslation = glm::vec3(xTranslation,yTranslation,zTranslation);

		boxTransform[i].mScale = wb::scale(randomScale);
		boxTransform[i].mRotate = wb::rotateXYZ(randomRotation);
		boxTransform[i].mTranslate = wb::translate(randomTranslation);
	}

	//generate projection matricies
	float fov = 100;
	float nearPlane = 0.1;
	float farPlane = 100;
	float aspectRatio = SCREEN_HEIGHT / SCREEN_WIDTH;

	perspectiveMatrix = wb::perspective(fov, aspectRatio, nearPlane, farPlane);
	orthoMatrix = wb::ortho(SCREEN_HEIGHT, aspectRatio, nearPlane, farPlane);
	
	//generate camera stuff
	float sensitivity = 0.05;
	float yaw = glm::radians<float>(-90);
	float pitch = glm::radians<float>(0);
	glm::vec3 startingPosition = glm::vec3(0, 0, 4);

	sceneCamera = camera(startingPosition, sensitivity, yaw, pitch, worldUp);

	//create view matrix

	glm::mat4 totalMatrix;

	while (!glfwWindowShouldClose(window)) {
		
		//Timing
		float time = (float)glfwGetTime();
		deltaTime = time - prevTime;
		prevTime = time;

		processInput(window);
		glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//std::cout << deltaTime << std::endl;

		glm::mat4 viewMatrix = wb::lookAt(sceneCamera.getCameraPosition(), sceneCamera.getTargetPosition(), worldUp);

		//update totalMatrix to be drawn
		//iProjection* iView* iTransform* vec4(in_Pos, 1.0)
		for (int i = 0; i < TRANSFORM_COUNT; i++)
		{
			if (usePerspective)
			{
				totalMatrix = projection.perspectiveMatrix * viewMatrix * boxTransform[i].getTransform(deltaTime);
			}
			else
			{
				totalMatrix = projection.orthoMatrix * viewMatrix * boxTransform[i].getTransform(deltaTime);
			}

			shader.use();

			shader.setInt("iTexture", 0);
			shader.setFloat("iTime", time);
			shader.setMat4("iTotal", totalMatrix);

			//TODO: Transform cube using uniform
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

float clampValue(float min, float max, float value)
{
	if (value < min)return min;
	else if (value > max)return max;
	else return value;
}

void resizeFrameBufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
	//TODO: Reset transform when R is pressed
	if (keycode == GLFW_KEY_1 && action == GLFW_PRESS) usePerspective = true;
	if (keycode == GLFW_KEY_2 && action == GLFW_PRESS) usePerspective = false;
	if (keycode == GLFW_KEY_ESCAPE && action == GLFW_PRESS)	glfwSetWindowShouldClose(window, true);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	float minFov = 0;
	float maxFov = 180;

	float temp = projection.mFov;

	temp = clampValue(minFov, maxFov, temp + yoffset);

	projection.updateFov(yoffset);

	std::cout << xoffset << " " << yoffset << std::endl;
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec2 cursorPosVec = glm::vec2(xpos, ypos);
	sceneCamera.point(cursorPosVec, worldUp);
}

void processInput(GLFWwindow* window)
{
	float moveSpeed = 0.025;
	//TODO: move camera using input
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) sceneCamera.move(camDirection::forward,moveSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) sceneCamera.move(camDirection::backwards,moveSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) sceneCamera.move(camDirection::left, moveSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) sceneCamera.move(camDirection::right, moveSpeed);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) sceneCamera.move(camDirection::up, moveSpeed);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) sceneCamera.move(camDirection::down, moveSpeed);
}
GLuint loadTexture(const char* filePath)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	int width, height, numComponents;
	unsigned char* textureData = stbi_load(filePath, &width, &height, &numComponents, 0);
	GLint format = numComponents == 3 ? GL_RGB : GL_RGBA;

	if (textureData) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("Failed to load texture");
	}
	return texture;
}

