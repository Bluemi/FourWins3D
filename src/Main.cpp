#include "Main.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	Main m;
	m.start();
}

void renderFunction()
{
}

Main::Main()
{}

void Main::start()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW - Window, ich komme :D", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Das ist jetzt schade, aber das macht nichts weil ich weiter arbeite" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}
