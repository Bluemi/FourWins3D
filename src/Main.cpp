#include "Main.hpp"

#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <math.h>

#include <debug/Debug.hpp>

const unsigned int Main::FRAME_INTERVAL = 40;

int main()
{
	Main m;
	m.init();
	m.run();
	m.close();
	return 0;
}

Main::Main()
	: shaderProgram(NULL)
{}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Main::init()
{
	// setup GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create Window
	window_ = glfwCreateWindow(800, 600, "4 wins", nullptr, nullptr);
	if (window_ == nullptr)
	{
		std::cout << "ERROR: Main::init(): can't create window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window_);

	// setup glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR: Main::init(): Failed to initialize GLAD" << std::endl;
		return;
	}

	// set Viewport
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

	// initiate vertices
	float vertices[] {
		// positions	   colors
		-0.5f, -0.5f, 0.f, 1.0f, 0.0f, 0.0f, // bottom left
		0.5f,  -0.5f, 0.f, 0.0f, 1.0f, 0.0f, // bottom right
		0.f,    0.5f, 0.f, 0.0f, 0.0f, 1.0f // top
	};

	// initiate VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// initiate VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Linking Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbind VAO
	glBindVertexArray(0);

	shaderProgram = new ShaderProgram("./src/shader/shaders/vertex.shader", "./src/shader/shaders/fragment.shader");
}

void Main::run()
{
	while (!glfwWindowShouldClose(window_))
	{
		processInput();
		render();
		glfwSwapBuffers(window_);
		glfwPollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_INTERVAL));
	}
}

void Main::close()
{
		glfwTerminate();
}

void Main::processInput()
{
	if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window_, true);
	}
}

void Main::render()
{
	clear();
	shaderProgram->use();
	glBindVertexArray(VAO);
	// render
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void Main::clear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
