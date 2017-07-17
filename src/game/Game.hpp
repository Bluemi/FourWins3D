#ifndef __GAME_CLASS__
#define __GAME_CLASS__

#include <vector>

#include <entity/Entity.hpp>
#include <camera/Camera.hpp>
#include <shader/ShaderProgram.hpp>
#include <texture/Texture.hpp>
#include <shape/CubeShape.hpp>
#include <game/container/BlockContainer.hpp>
#include "Controller.hpp"

class Game
{
	public:
		Game();
		void init(const unsigned int screenWidth, const unsigned int screenHeight);
		void tick();
		void render();
		void addBlock();
	private:
		Camera camera;
		ShaderProgram shader3D;
		Texture texture;
		CubeShape cubeShape;
		Controller controller;

		BlockContainer blocks;
};

#endif
