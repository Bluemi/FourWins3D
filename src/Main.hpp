#ifndef __MAIN_CLASS__
#define __MAIN_CLASS__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <shader/ShaderProgram.hpp>
#include <camera/Camera.hpp>

class Main
{
	public:
		static const unsigned int FRAME_INTERVAL;

		Main();
		void init();
		void run();
		void close();

	private:
		void processInput();
		void render();
		void clear();

		GLFWwindow* window_;
		unsigned int VBO;
		unsigned int VAO;
		unsigned int texture0;

		unsigned int screenWidth;
		unsigned int screenHeight;

		ShaderProgram *shaderProgram;
		Camera *camera;

		std::vector<glm::vec3> cubePositions;
};

#endif
