#include "MouseManager.hpp"

#include <iostream>

MouseListener *MouseManager::listener;
glm::vec2 MouseManager::current;
glm::vec2 MouseManager::last;
bool MouseManager::hasGotFirstPosition;

void MouseManager::init(GLFWwindow *window)
{
	glfwSetCursorPosCallback(window, mouseCallback);
	listener = nullptr;
	current = glm::vec2(0.0f, 0.0f);
	last = glm::vec2(0.0f, 0.0f);
}

void MouseManager::call()
{
	if (listener != nullptr)
	{
		listener->onMouseMoved(current-last);
	}
	glm::vec2 diff = (current-last);
	if (diff.x != 0.0f && (diff.y != 0.0f))
		std::cout << diff.x << " " << diff.y << std::endl;
	last = current;
}

void MouseManager::capture(MouseListener *l)
{
	listener = l;
}

void MouseManager::mouseCallback(GLFWwindow *window, double x, double y)
{
	current = glm::vec2(x, y);
	if (!hasGotFirstPosition)
	{
		last = current;
		hasGotFirstPosition = true;
	}
}

MouseManager::MouseManager() {}
