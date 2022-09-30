#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <stdio.h>

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void resizeFrameBufferCallback(GLFWwindow* window, int width, int height);

//Vertex shader source code
const char* vertexShaderSource =
"#version 330							\n"
"layout (location = 0) in vec3 in_Pos;  \n"
"void main(){							\n"
"	gl_Position = vec4(in_Pos, 1.0);	\n"
"}										\0";

//Vertex shader with multiple attributes
const char* coloredVertexShaderSource =
"#version 330							\n"
"layout (location = 0) in vec3 in_Pos;	\n"
"layout (location = 1) in vec4 in_Color;\n"
"										\n"
"out vec4 Color;						\n"
"void main()							\n"
"{										\n"
"	Color = in_Color;					\n"
"	gl_Position = vec4(in_Pos,1.0);		\n"
"};										\n";

//Fragment shader source code
const char* fragmentShaderSource =
"#version 330				\n"
"out vec4 FragColor;		\n"
"void main(){				\n"
"	FragColor = vec4(1.0);	\n"
"}							\0";

//Fragment shader with colors
const char* coloredFragmentShaderSource =
"#version 330				\n"
"out vec4 FragColor;		\n"
"in vec4 Color;				\n"
"void main()				\n"
"{							\n"
"FragColor = Color;			\n"
"}							\n";

//Vertex data array
const float quadVertexData[] = {
//	x		y		z		r		g		b		a
   -0.5f,  -0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	//bottom left
	0.0f,  -0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	//bottom right
   -0.25f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	//top center
	0.25f,  0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	//top right
	
};

const unsigned int quadIndices[] = {
	0,1,2, //First triangle
	1,3,2  //Second triangle
};

const float triforceVertexData[] = {
	//	x		y		z		r		g		b		a
	   -0.5f,  -0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	//bottom left
		0.0f,  -0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	//bottom right
	   -0.25f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	//top center
		0.25f,  0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	//top right

};

const unsigned int triforceIndices[] = {
	0,1,2, //First triangle
	1,3,2  //Second triangle
};

bool wireFrame = true;

enum objectType
{
	quad,
	triforce,
	strip
};

objectType objectToDraw = quad;

int main() {
	if (!glfwInit()) {
		printf("glfw failed to init");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGLExample", 0, 0);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("glew failed to init");
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, resizeFrameBufferCallback);
	glfwSetKeyCallback(window, keyboardCallback);

	//Create and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &coloredVertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Get vertex shader compilation status and output info log
	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("Failed to compile vertex shader %s", infoLog);
	}
	
	//Create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &coloredFragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	//Get fragment shader compilation status and output info log
	success;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("Failed to compile vertex shader %s", infoLog);
	}

	//Create shader program
	GLuint shaderProgram = glCreateProgram();

	//Attach vertex and fragment shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//Link shader program
	glLinkProgram(shaderProgram);

	//Check for link status and output errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Failed to link shader program: %s", infoLog);
		return -1;
	}

	//TODO: Delete vertex + fragment shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Quad start
	//Create and bind Vertex Array Object (VAO)
	GLuint quadVertexArrayObject;
	glGenVertexArrays(1, &quadVertexArrayObject);
	glBindVertexArray(quadVertexArrayObject);

	//Create and bind Vertex Buffer Object (VBO), fill with vertexData
	GLuint quadVertexBufferObject;
	glGenBuffers(1, &quadVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, quadVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertexData), quadVertexData, GL_STATIC_DRAW);

	//Indices data
	GLuint quadElementBufferObject;
	glGenBuffers(1, &quadElementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

	//TODO: Define vertex attribute layout
	//glVertexAttribPointer(...)
	//glEnableVertexAttribArray(...)

	//position (3 floats, XYZ)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)0);
	glEnableVertexAttribArray(0);

	//color (4 floats, RGBA)
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	//Quad end

	//triforce start
	//Create and bind Vertex Array Object (VAO)
	GLuint triforceVertexArrayObject;
	glGenVertexArrays(1, &triforceVertexArrayObject);
	glBindVertexArray(triforceVertexArrayObject);

	//Create and bind Vertex Buffer Object (VBO), fill with vertexData
	GLuint triforceVertexBufferObject;
	glGenBuffers(1, &triforceVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, triforceVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triforceVertexData), triforceVertexData, GL_STATIC_DRAW);

	//Indices data
	GLuint triforceElementBufferObject;
	glGenBuffers(1, &triforceElementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triforceElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triforceIndices), triforceIndices, GL_STATIC_DRAW);

	//TODO: Define vertex attribute layout
	//glVertexAttribPointer(...)
	//glEnableVertexAttribArray(...)

	//position (3 floats, XYZ)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)0);
	glEnableVertexAttribArray(0);

	//color (4 floats, RGBA)
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	//triforce end

	//wireframe mode
	//glPolygonMode(GL_FRONT, GL_FILL);

	//Enable face culling
	glEnable(GL_CULL_FACE);

	//Set culling to front or back (currently set to back)
	glCullFace(GL_BACK);

	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO:Use shader program
		glUseProgram(shaderProgram);

		GLenum polygonMode = wireFrame ? GL_LINE : GL_FILL;
		glPolygonMode(GL_FRONT, polygonMode);
		
		//TODO: Draw triangle (3 indices!)
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		switch (objectToDraw)
		{
		case quad:
			glBindVertexArray(quadElementBufferObject);
			break;
		case triforce:
			glBindVertexArray(triforceElementBufferObject);
			break;
		case strip:
			//glBindVertexArray(stripElementBufferObject);
			break;
		};
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && GLFW_PRESS)
	{
		printf("pressed w\n");
		wireFrame = !wireFrame;
	}
	if (key == GLFW_KEY_1 && GLFW_PRESS)
	{
		objectToDraw = quad;
	}
	if (key == GLFW_KEY_2 && GLFW_PRESS)
	{
		objectToDraw = triforce;
	}
	if (key == GLFW_KEY_3 && GLFW_PRESS)
	{
		objectToDraw = strip;
	}
}

void resizeFrameBufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}