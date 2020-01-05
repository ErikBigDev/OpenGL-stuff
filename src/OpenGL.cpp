#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void* userParam)
{
	/*fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);*/

	std::string strType;
	std::string strSeverity;
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		strSeverity = "NOTIFICATION";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		strSeverity = "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		strSeverity = "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		strSeverity = "HIGH";
		break;
	}
	
	switch (type)
	{
	case GL_DEBUG_TYPE_OTHER:
		strType = "OTHER";
		break;
	case GL_DEBUG_TYPE_MARKER:
		strType = "MARKER";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		strType = "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		strType = "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		strType = "DEPRECATED BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		strType = "UNDEFINED BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_ERROR:
		strType = "ERROR";
		break;
	default:
		strType = "IDK";
	}

	std::cout << "["<< strType.c_str() << "]: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "")
		<< ", Severity: " << strSeverity.c_str() << ", " << message << "\n";
	if (type == GL_DEBUG_TYPE_ERROR)
		__debugbreak();
}

int main()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	//Initialize glew
	if (glewInit() != GLEW_OK)
		return -1;

	std::cout << glGetString(GL_VERSION) << "\n";

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, NULL);
	/////////////////////////////////////////////////////

	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	VertexArray va;
	VertexBuffer vb(positions, 4 * 2 * sizeof(float));
	VertexBufferLayout layout;

	va.AddBuffer(vb, layout);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	IndexBuffer ib(indices, 6);

	Shader shader("res/shaders/Basic.vert", "res/shaders/Basic.frag");
	shader.Bind();

	//shader.SetUniform4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);

	va.Unbind();
	shader.Unbind();
	vb.Unbind();
	ib.Unbind();

	Renderer renderer;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		renderer.Draw(va, ib, shader);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}