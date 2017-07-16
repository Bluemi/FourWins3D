#include "Main.hpp"

#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <math.h>

#include <images/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <debug/Debug.hpp>
#include <interaction/MouseManager.hpp>

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
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), 0.0f, -90.0f);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* w, double x, double y)
{
	std::cout << x << "\t" << y << std::endl;
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

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// set Viewport
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
	MouseManager::init(window_);

	camera->captureMouse();

	// initiate vertices
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// initiate VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// initiate VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Linking Vertex Attributes
	const unsigned stripe = 5*sizeof(float);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stripe, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stripe, (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stripe, (void*)(6*sizeof(float)));
	//glEnableVertexAttribArray(2);

	// texture 0
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	std::string path = "./res/container.jpg";
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		Debug::out << Debug::error << "couldnt load " << path << Debug::endl;
	}

	stbi_image_free(data);

	// unbind VAO
	glBindVertexArray(0);

	shaderProgram = new ShaderProgram("./src/shader/shaders/vertex.shader", "./src/shader/shaders/fragment.shader");

	shaderProgram->use();
	shaderProgram->setInt("texture0", 0);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), screenWidth/(float)screenHeight, 0.1f, 100.f);
	shaderProgram->setMat4("projection", projection);

	cubePositions.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	cubePositions.push_back(glm::vec3(-2.0f, 1.0f, -5.0f));
	cubePositions.push_back(glm::vec3(5.0f, -3.f, -7.0f));
}

void Main::run()
{
	while (!glfwWindowShouldClose(window_))
	{
		processInput();
		render();
		glfwPollEvents();
		MouseManager::call();
		std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_INTERVAL));
	}
}

void Main::close()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete shaderProgram;
	glfwTerminate();
}

void Main::processInput()
{
	if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window_, true);
	}
	if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
		camera->goForward();
	if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
		camera->goBackward();
	if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
		camera->goLeft();
	if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
		camera->goRight();
}

void Main::render()
{
	clear();
	shaderProgram->use();

	glm::mat4 view = camera->getLookAt();

	shaderProgram->setMat4("view", view);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glBindVertexArray(VAO);
	// render
	for (glm::vec3 pos : cubePositions)
	{
		glm::mat4 model;
		model = glm::translate(model, pos);
		shaderProgram->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
	glfwSwapBuffers(window_);
}

void Main::clear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
