#ifndef __MAIN_CLASS__
#define __MAIN_CLASS__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader/ShaderProgram.hpp>

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
		ShaderProgram *shaderProgram;
};

#endif
