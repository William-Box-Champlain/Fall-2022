#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "camera.h"
#include "Transformations.h"

//#include <glm/glm.hpp>
//#include <glm/matrix.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"

transform boxTransform;
camera sceneCamera;

void processInput(GLFWwindow* window);
void resizeFrameBufferCallback(GLFWwindow* window, int width, int height);
void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);
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

	//set transformation rates on box
	boxTransform.setRotation(glm::vec3(0.025, 0.025, 0.025));
	boxTransform.setScale(0.1);
	boxTransform.setTranslation(glm::vec3(0.1, 0.1, 0.1));

	//generate projection matricies
	float fov = 100;
	float nearPlane = 0.1;
	float farPlane = 100;
	float aspectRatio = SCREEN_HEIGHT / SCREEN_WIDTH;

	glm::mat4 perspectiveMatrix = wb::perspective(fov, aspectRatio, nearPlane, farPlane);
	glm::mat4 orthoMatrix = wb::ortho(SCREEN_HEIGHT, aspectRatio, nearPlane, farPlane);

	//generate camera stuff
	float sensitivity = 1.0;
	float yaw = glm::radians<float>(-90);
	float pitch = glm::radians<float>(0);
	glm::vec3 startingPosition = glm::vec3(0, 0, 2);
	glm::vec3 worldUp = glm::vec3(0, 1, 0);

	sceneCamera = camera(startingPosition, sensitivity, yaw, pitch, worldUp);

	//create view matrix
	glm::mat4 viewMatrix = wb::lookAt(sceneCamera.getCameraPosition(), sceneCamera.getTargetPosition(), worldUp);

	glm::mat4 totalMatrix;

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Timing
		float time = (float)glfwGetTime();
		deltaTime = time - prevTime;
		prevTime = time;

		std::cout << deltaTime << std::endl;

		//iProjection* iView* iTransform* vec4(in_Pos, 1.0)
		totalMatrix = orthoMatrix * viewMatrix * boxTransform.getTransform(deltaTime);

		shader.use();
		
		shader.setInt("iTexture", 0);
		shader.setFloat("iTime", time);
		/*shader.setMat4("iTransform", boxTransform.getTransform(deltaTime));
		shader.setMat4("iView", viewMatrix);
		shader.setMat4("iProjection", perspectiveMatrix);*/
		shader.setMat4("iTotal", totalMatrix);

		//TODO: Transform cube using uniform

		glDrawArrays(GL_TRIANGLES, 0, 36);
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
	//TODO: Reset transform when R is pressed
	if (keycode == GLFW_KEY_R && action == GLFW_PRESS) boxTransform.reset();
}

void processInput(GLFWwindow* window)
{

	//TODO: Change position, rotation, scale using input
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
	{
		boxTransform.rotate(cwY);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		boxTransform.rotate(ccY);
	}

	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		boxTransform.rotate(cwX);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		boxTransform.rotate(ccX);
	}

	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		boxTransform.rotate(cwZ);
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		boxTransform.rotate(ccZ);
	}

	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		boxTransform.translate(right);
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		boxTransform.translate(left);
	}

	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		boxTransform.translate(up);
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		boxTransform.translate(down);
	}

	else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		boxTransform.scale(grow);
	}
	else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		boxTransform.scale(shrink);
	}
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

