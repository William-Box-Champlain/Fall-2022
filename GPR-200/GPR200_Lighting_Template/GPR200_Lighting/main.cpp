#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "EW/Shader.h"
#include "EW/EwMath.h"
#include "EW/Camera.h"
#include "EW/Mesh.h"
#include "EW/Transform.h"
#include "EW/ShapeGen.h"

void processInput(GLFWwindow* window);
void resizeFrameBufferCallback(GLFWwindow* window, int width, int height);
void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);
float randomRange(float min, float max);
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

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

/* Button to lock / unlock mouse
* 1 = right, 2 = middle
* Mouse will start locked. Unlock it to use UI
* */
const int MOUSE_TOGGLE_BUTTON = 1;
const float MOUSE_SENSITIVITY = 0.1f;

Camera camera((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);

Transform cubeTransform;
Transform sphereTransform;
Transform coneTransform;
Transform lightTransform;

glm::vec3 bgColor = glm::vec3(0);
glm::vec3 lightColor = glm::vec3(1.0f);
glm::vec3 lightOrbitCenter = glm::vec3(0,3.0f,0);
float lightOrbitRadius = 5.0f;
float lightOrbitSpeed = 1.0f;

bool drawAsPoints = false;

//TODO: Add material variables. HINT: A struct is helpful!

float ambientK = 0.5f;
float diffuseK = 0.5f;
float specularK = 0.5f;

glm::vec3 ambientColor = lightColor * ambientK;

int main() {
	if (!glfwInit()) {
		printf("glfw failed to init");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lighting", 0, 0);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("glew failed to init");
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, resizeFrameBufferCallback);
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetScrollCallback(window, mouseScrollCallback);
	glfwSetCursorPosCallback(window, mousePosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	// Setup UI Platform/Renderer backends
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	//Dark UI theme.
	ImGui::StyleColorsDark();

	//Used to draw shapes. This is the shader you will be completing.
	Shader litShader("shaders/defaultLit.vert", "shaders/defaultLit.frag");

	//Used to draw light
	Shader unlitShader("shaders/defaultLit.vert", "shaders/unlit.frag");

	MeshData cubeMeshData;
	createCube(1.0f, 1.0f, 1.0f, glm::vec3(1.0f), cubeMeshData);
	MeshData sphereMeshData;
	createSphere(0.5f, 64.0f, glm::vec3(1.0f), sphereMeshData);
	MeshData coneMeshData;
	createCone(0.75f, 1.0f, 64.0f, glm::vec3(1.0f), coneMeshData);

	Mesh cubeMesh(&cubeMeshData);
	Mesh sphereMesh(&sphereMeshData);
	Mesh coneMesh(&coneMeshData);

	//Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glPointSize(3.0f);

	//Initialize positions
	cubeTransform.position = glm::vec3(-2.0f, 0.0f, 0.0f);
	sphereTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	coneTransform.position = glm::vec3(2.0f,0.0f,0.0f);

	lightTransform.scale = glm::vec3(0.5f);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(bgColor.r,bgColor.g,bgColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		float time = (float)glfwGetTime();
		deltaTime = time - lastFrameTime;
		lastFrameTime = time;

		//Light position 
		lightTransform.position = lightOrbitCenter;
		lightTransform.position.x += cosf(time * lightOrbitSpeed) * lightOrbitRadius;
		lightTransform.position.z += sinf(time * lightOrbitSpeed) * lightOrbitRadius;

		//Draw
		litShader.use();
		litShader.setMat4("uProjection", camera.getProjectionMatrix());
		litShader.setMat4("uView", camera.getViewMatrix());

		//TODO: Set material uniforms, lightPos, eyePos
		litShader.setVec3("uLightPos", lightTransform.position);
		litShader.setVec3("uEyePos", camera.position);

		litShader.setVec3("uLightColor", lightColor);
		litShader.setFloat("uAmbiantK", ambientK);
		litShader.setFloat("uDiffuseK", diffuseK);
		litShader.setFloat("uSpecularK", specularK);

		litShader.setVec3("uLightColor", lightColor);

		//Draw cube
		litShader.setMat4("uModel", cubeTransform.getModelMatrix());
		cubeMesh.draw(drawAsPoints);

		//Draw sphere
		litShader.setMat4("uModel", sphereTransform.getModelMatrix());
		sphereMesh.draw(drawAsPoints);

		//Draw cone
		litShader.setMat4("uModel", coneTransform.getModelMatrix());
		coneMesh.draw(drawAsPoints);

		//Draw light as a small sphere using unlit shader, ironically.
		unlitShader.use();
		unlitShader.setMat4("uProjection", camera.getProjectionMatrix());
		unlitShader.setMat4("uView", camera.getViewMatrix());
		unlitShader.setMat4("uModel", lightTransform.getModelMatrix());
		unlitShader.setVec3("uColor", lightColor);
		sphereMesh.draw(drawAsPoints);

		//Draw UI
		ImGui::Begin("Settings");

		//TODO: Add material settings

		ImGui::ColorEdit3("Light Color", &lightColor.r);
		ImGui::SliderFloat3("Light Orbit Center",&lightOrbitCenter.r,-5.0f,5.0f);
		ImGui::SliderFloat("Light Orbit Radius", &lightOrbitRadius, 0.0f, 5.0f);
		ImGui::SliderFloat("Light Orbit Speed", &lightOrbitSpeed, 0.0f, 3.0f);
		ImGui::SliderFloat("AmbientK", &ambientK, 0.0f, 1.0f);
		ImGui::SliderFloat("DiffuseK", &diffuseK, 0.0f, 1.0f);
		ImGui::SliderFloat("SpecularK", &specularK, 0.0f, 1.0f);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwPollEvents();

		glfwSwapBuffers(window);
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
	//Toggle between drawing as points
	if (keycode == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		drawAsPoints = !drawAsPoints;
	}
	//Reset camera
	if (keycode == GLFW_KEY_R && action == GLFW_PRESS) {
		camera.position = glm::vec3(0,0,5);
		camera.yaw = -90.0f;
		camera.pitch = 0.0f;
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
	if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
		return;
	}
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
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//Toggle cursor lock
	if (button == MOUSE_TOGGLE_BUTTON && action == GLFW_PRESS) {
		int inputMode = glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
		glfwSetInputMode(window, GLFW_CURSOR, inputMode);
		glfwGetCursorPos(window, &prevMouseX, &prevMouseY);
	}
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

	glm::vec3 forward = camera.getForward();
	glm::vec3 right = glm::normalize(glm::cross(forward, WORLD_UP));
	glm::vec3 up = glm::normalize(glm::cross(forward, right));
	camera.position += forward * getAxis(window, GLFW_KEY_W, GLFW_KEY_S) * moveAmnt;
	camera.position += right * getAxis(window, GLFW_KEY_D, GLFW_KEY_A) * moveAmnt;
	camera.position += up * getAxis(window, GLFW_KEY_Q, GLFW_KEY_E) * moveAmnt;
}
