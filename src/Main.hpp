#ifndef __MAIN_CLASS__
#define __MAIN_CLASS__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <shader/ShaderProgram.hpp>
#include <camera/Camera.hpp>
#include <shape/CubeShape.hpp>
#include <texture/Texture.hpp>
#include <entity/Entity.hpp>

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

		unsigned int screenWidth;
		unsigned int screenHeight;

		ShaderProgram *shaderProgram;
		Camera *camera;
		CubeShape *cubeShape;
		Texture *texture;

		std::vector<Entity> entities;
};

#endif
