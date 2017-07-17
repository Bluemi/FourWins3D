#ifndef __MAIN_CLASS__
#define __MAIN_CLASS__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <game/Game.hpp>

class Main
{
	public:
		static const unsigned int FRAME_INTERVAL;

		Main();
		void init();
		void run();
		void close();

	private:
		void render(Game &game);
		void clear();

		void processInput();

		GLFWwindow* window_;

		unsigned int screenWidth;
		unsigned int screenHeight;
};

#endif
