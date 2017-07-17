#ifndef __GAME_CLASS__
#define __GAME_CLASS__

#include <vector>

#include <entity/Entity.hpp>
#include <camera/Camera.hpp>
#include <shader/ShaderProgram.hpp>
#include <texture/Texture.hpp>
#include <shape/CubeShape.hpp>
#include <game/container/BlockContainer.hpp>

class Game
{
	public:
		Game();
		void init(const unsigned int screenWidth, const unsigned int screenHeight);
		void tick();
		void render();
	private:
		Camera camera;
		ShaderProgram shader3D;
		Texture texture;
		CubeShape cubeShape;

		BlockContainer blocks;
};

#endif
