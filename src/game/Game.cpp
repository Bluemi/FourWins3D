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

	shader3D.load("./src/shader/shaders/vertex3d.shader", "./src/shader/shaders/fragment3d.shader");
	shader3D.use();
	shader3D.setMat4("projection", glm::perspective(glm::radians(45.0f), screenWidth/(float)screenHeight, 0.1f, 100.f));

	// texture
	texture.load("./res/container.jpg");

	// shape
	cubeShape.load();

	blocks.insert(0, 0, 0, new Entity(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), &cubeShape, &texture));
	blocks.insert(1, 0, 0, new Entity(glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), &cubeShape, &texture));
}

void Game::tick()
{
	camera.tick();
}

void Game::render()
{
	shader3D.use();
	shader3D.setMat4("view", camera.getLookAt());

	for (Entity *e : blocks.getList())
	{
		e->getTexture()->use();
		e->getShape()->use();
		shader3D.setMat4("model", e->getModel());
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void Game::addBlock()
{
	glm::vec3 newPosition;
	if (blocks.canPlaceBlockHere(camera.getPosition(), camera.getDirection(), newPosition))
	{
		std::cout << "block added" << std::endl;
		blocks.insert((int)newPosition.x, (int)newPosition.y, (int)newPosition.z, new Entity(newPosition, glm::vec3(1, 0, 0), &cubeShape, &texture));
	}
	else
	{
		std::cout << "can't add block" << std::endl;
	}
}
