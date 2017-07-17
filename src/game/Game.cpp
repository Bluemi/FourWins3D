#include "Game.hpp"

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Game::Game()
	: camera(glm::vec3(0.0f, 0.0f, 3.0f), 0.0f, -90.f), controller()
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

	blocks.insert(0, 0, 0, new Entity(glm::vec3(0, 0, 0), glm::vec3(0.5f, 0.5f, 0.5f), &cubeShape, &texture));
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
	glDrawArrays(GL_TRIANGLES, 0, 12);
}

void Game::addBlock()
{
	glm::vec3 newPosition;
	if (blocks.canPlaceBlockHere(camera.getPosition(), camera.getDirection(), newPosition))
	{
		blocks.insert((int)newPosition.x, (int)newPosition.y, (int)newPosition.z, new Entity(newPosition, glm::vec3(0.7f, 0.2f, 0.2f), &cubeShape, &texture));
	}
}
