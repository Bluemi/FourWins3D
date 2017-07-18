#include "Game.hpp"

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <math/vec3i.hpp>

Game::Game()
	: camera(glm::vec3(0.0f, 0.0f, 3.0f), 0.0f, -90.f), controller(), nextBlockRed(true)
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

	blocks.insert(vec3i(), new Entity(glm::vec3(0, 0, 0), glm::vec3(0.5f, 0.5f, 0.5f), &cubeShape, &texture));
}

void Game::tick()
{
	camera.tick();
}

void Game::render()
{
	gameShader.use();
	gameShader.setMat4("view", camera.getLookAt());

	// blocks
	for (Entity *e : blocks.getList())
	{
		e->getTexture()->use();
		e->getShape()->use();
		gameShader.setVec3("color", e->getColor());
		gameShader.setMat4("model", e->getModel());
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


	guiShader.use();
	crossShape.use();
	if (nextBlockRed) {
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
		glm::vec3 c;
		if (nextBlockRed)
		{
			c = glm::vec3(0.7f, 0.3f, 0.3f);
		} else {
			c = glm::vec3(0.6f, 0.6f, 0.2f);
		}
		nextBlockRed = !nextBlockRed;
		blocks.insert(newPosition, new Entity(newPosition.toVec3(), c, &cubeShape, &texture));
	}
	else
		std::cout << "cant place block" << std::endl;
}
