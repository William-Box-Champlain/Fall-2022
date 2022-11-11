#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "EW/Shader.h"
#include "EW/EwMath.h"
#include "EW/Camera.h"
#include "EW/Mesh.h"
#include "EW/Transform.h"
#include "ShapeGen.h"

void processInput(GLFWwindow* window);
void resizeFrameBufferCallback(GLFWwindow* window, int width, int height);
void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);
float randomRange(float min, float max);
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void mousePosCallback(GLFWwindow* window, double xpos, double ypos);

float lastFrameTime;
float deltaTime;

int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 640;

float moveSpeed = 1.0f;
float rotateSpeed = 3.0f;
float scaleSpeed = 1.0f;

double prevMouseX;
double prevMouseY;
bool firstMouseInput = false;
const float MOUSE_SENSITIVITY = 0.1f;

Camera camera((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);

Transform cubeTransform;
//TODO: Create plane, cone, sphere transform

//Press "C" to toggle back-face culling
bool cullingEnabled = true;

//Press SPACE to toggle between drawing points vs triangles.
//Point drawing will use glDrawArrays, so you can test vertices independently.
bool drawAsPoints = false; 

int main() {
	if (!glfwInit()) {
		printf("glfw failed to init");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Procedural Geometry", 0, 0);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("glew failed to init");
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, resizeFrameBufferCallback);
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetScrollCallback(window, mouseScrollCallback);
	glfwSetCursorPosCallback(window, mousePosCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");

	MeshData cubeMeshData;
	createCube(1.0f, 1.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), cubeMeshData);
	//TODO: create MeshData for plane, cone, sphere. Use different colors for each!

	Mesh cubeMesh(&cubeMeshData);
	//TODO: create Mesh for plane, cone, sphere

	//Enable back-face culling
	if (cullingEnabled) {
		glEnable(GL_CULL_FACE);
	}
	glCullFace(GL_BACK);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(3.0f);

	//Initialize positions
	cubeTransform.position = glm::vec3(0.0f,0.0f,0.0f);

	//Todo: Change plane, cone, sphere positions

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.1f, 0.15f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float time = (float)glfwGetTime();
		deltaTime = time - lastFrameTime;
		lastFrameTime = time;

		shader.use();
		shader.setMat4("Projection", camera.getProjectionMatrix());
		shader.setMat4("View", camera.getViewMatrix());

		//Draw cube
		shader.setMat4("Model", cubeTransform.getModelMatrix());
		cubeMesh.draw(drawAsPoints);

		//TODO: Draw plane, cone, sphere
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void resizeFrameBufferCallback(GLFWwindow* window, int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	camera.aspectRatio = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	glViewport(0, 0, width, height);
}

void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
	if (keycode == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (keycode == GLFW_KEY_1 && action == GLFW_PRESS) {
		camera.ortho = false;
	}
	if (keycode == GLFW_KEY_2 && action == GLFW_PRESS) {
		camera.ortho = true;
	}
	if (keycode == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		drawAsPoints = !drawAsPoints;
	} 
	if (keycode == GLFW_KEY_C && action == GLFW_PRESS) {
		cullingEnabled = !cullingEnabled;
		if (cullingEnabled) {
			glEnable(GL_CULL_FACE);
		}
		else {
			glDisable(GL_CULL_FACE);
		}
	}
	//Reset
	if (keycode == GLFW_KEY_R && action == GLFW_PRESS) {
		camera.position = glm::vec3(0,0,5);
		camera.yaw = -90.0f;
		camera.pitch = 0.0f;
		camera.updateVectors();
		firstMouseInput = false;
	}
}

float randomRange(float min, float max)
{
	return min + (max - min) * ((float)rand() / (float)RAND_MAX);
}

void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (abs(yoffset) > 0) {
		camera.fov -= (float)yoffset * camera.zoomSpeed;
		if (camera.fov < 0.0f) {
			camera.fov = 0.0f;
		}
		else if (camera.fov > 180.0f) {
			camera.fov = 180.0f;
		}
	}
}

void mousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (!firstMouseInput) {
		prevMouseX = xpos;
		prevMouseY = ypos;
		firstMouseInput = true;
	}
	camera.yaw += (float)(xpos - prevMouseX) * MOUSE_SENSITIVITY;
	camera.pitch -= (float)(ypos - prevMouseY) * MOUSE_SENSITIVITY;

	if (camera.pitch < -89.9f) {
		camera.pitch = -89.9f;
	}
	else if (camera.pitch > 89.9f) {
		camera.pitch = 89.9f;
	}
	prevMouseX = xpos;
	prevMouseY = ypos;

	camera.updateVectors();
}

float getAxis(GLFWwindow* window, int positiveKey, int negativeKey) {
	float axis = 0.0f;
	if (glfwGetKey(window, positiveKey)) {
		axis++;
	}
	if (glfwGetKey(window, negativeKey)) {
		axis--;
	}
	return axis;
}

void processInput(GLFWwindow* window) {
	float moveAmnt = camera.moveSpeed * deltaTime;
	camera.position += camera.forward * getAxis(window, GLFW_KEY_W, GLFW_KEY_S) * moveAmnt;
	camera.position += camera.right * getAxis(window, GLFW_KEY_D, GLFW_KEY_A) * moveAmnt;
	camera.position += camera.up * getAxis(window, GLFW_KEY_Q, GLFW_KEY_E) * moveAmnt;
}
