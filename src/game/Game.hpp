#ifndef __GAME_CLASS__
#define __GAME_CLASS__

#include <vector>

#include <entity/Entity.hpp>
#include <camera/Camera.hpp>
#include <shader/ShaderProgram.hpp>
#include <texture/Texture.hpp>
#include <shape/CubeShape.hpp>
#include <shape/CrossShape.hpp>
#include <game/container/BlockContainer.hpp>
#include <game/container/BlockType.hpp>
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
		ShaderProgram gameShader;
		ShaderProgram guiShader;
		Texture texture;
		CubeShape cubeShape;
		CrossShape crossShape;
		Controller controller;

		BlockContainer blocks;

		BlockType nBlockType;
};

#endif
