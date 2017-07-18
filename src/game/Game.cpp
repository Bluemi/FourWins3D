#include "Game.hpp"

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <math/vec3i.hpp>
#include <game/container/BlockType.hpp>

Game::Game()
	: camera(glm::vec3(0.0f, 0.0f, 3.0f), 0.0f, -90.f), controller(), nBlockType(BlockType::RED)
{}

void Game::init(const unsigned int screenWidth, const unsigned int screenHeight)
{
	camera.captureMouse();
	camera.captureKeyboard();

	controller.init(this);

	guiShader.load("./src/shader/shaders/gui.vs", "./src/shader/shaders/gui.fs");

	gameShader.load("./src/shader/shaders/game.vs", "./src/shader/shaders/game.fs");
	gameShader.use();
	gameShader.setMat4("projection", glm::perspective(glm::radians(45.0f), screenWidth/(float)screenHeight, 0.1f, 100.f));

	// texture
	texture.load("./res/container.jpg");

	// shapes
	cubeShape.load();
	crossShape.load();

	blocks.insert(vec3i(), new Entity(glm::vec3(0, 0, 0), BlockType::NONE, &cubeShape, &texture));
}

void Game::tick()
{
	camera.tick();
}

void Game::render()
{
	blocks.tick();
	gameShader.use();
	gameShader.setMat4("view", camera.getLookAt());

	// blocks
	for (Entity *e : blocks.getList())
	{
		e->getTexture()->use();
		e->getShape()->use();
		gameShader.setVec3("color", toColor(e->getBlockType()));
		gameShader.setMat4("model", e->getModel());
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


	guiShader.use();
	crossShape.use();
	if (nBlockType == BlockType::RED) {
		guiShader.setVec3("color", glm::vec3(0.7, 0.1f, 0.1f));
	} else {
		guiShader.setVec3("color", glm::vec3(0.5, 0.5f, 0.1f));
	}
	glDrawArrays(GL_TRIANGLES, 0, 12);
}

void Game::addBlock()
{
	vec3i newPosition;
	if (blocks.canPlaceBlockHere(camera.getPosition(), camera.getDirection(), newPosition))
	{
		std::cout << "placed block" << std::endl;
		blocks.insert(newPosition, new Entity(newPosition.toVec3(), nBlockType, &cubeShape, &texture));
		nBlockType = nextBlockType(nBlockType);
		checkForWinners(newPosition);
	}
	else
		std::cout << "cant place block" << std::endl;
}

void Game::checkForWinners(const vec3i &position)
{
	std::vector<Entity*> winnerEntities;
	if (blocks.checkWinner(position, winnerEntities))
	{
		for (Entity* e : winnerEntities)
			e->winner();
		blocks.randomShit();
	}
}

void Game::restart()
{
	blocks.clearAndDelete();
	blocks.insert(vec3i(), new Entity(glm::vec3(0, 0, 0), BlockType::NONE, &cubeShape, &texture));
}
