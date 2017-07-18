#include "Controller.hpp"

#include <interaction/KeyboardManager.hpp>

Controller::Controller()
{}

void Controller::init(Game *game)
{
	this->game = game;
	KeyboardManager::capture(this);
}

void Controller::onKeyPressed(int key)
{
	switch (key)
	{
		case GLFW_KEY_E:
			game->addBlock();
			break;
		case GLFW_KEY_R:
			game->restart();
			break;
		default:
			break;
	}
}

void Controller::onKeyReleased(int key)
{
}
