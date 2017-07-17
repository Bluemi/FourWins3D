#include "Main.hpp"

#include <unistd.h>
#include <thread>
#include <chrono>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <debug/Debug.hpp>
#include <interaction/MouseManager.hpp>
#include <interaction/KeyboardManager.hpp>

const unsigned int Main::FRAME_INTERVAL = 30;

int main()
{
	Main m;
	m.init();
	m.run();
	m.close();
	return 0;
}

Main::Main()
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
	screenWidth = 800;
	screenHeight = 600;
	if (window_ == nullptr)
	{
		Debug::out << Debug::error << "Main::init(): can't create window" << Debug::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window_);

	// setup glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Debug::out << Debug::error << "Main::init(): Failed to initialize GLAD" << Debug::endl;
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// set Viewport
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
	MouseManager::init(window_);
	KeyboardManager::init(window_);
}

void Main::processInput()
{
	if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window_, true);
}

void Main::run()
{
	Game game;
	game.init(screenWidth, screenHeight);
	while (!glfwWindowShouldClose(window_))
	{
		glfwPollEvents();
		MouseManager::call();
		KeyboardManager::call();
		processInput();
		game.tick();
		render(game);
		std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_INTERVAL));
	}
}

void Main::close()
{
	glfwTerminate();
}

void Main::render(Game &game)
{
	clear();
	game.render();
	glfwSwapBuffers(window_);
}

void Main::clear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
