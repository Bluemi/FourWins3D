#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <math.h>

#include <interaction/MouseManager.hpp>
#include <interaction/KeyboardManager.hpp>

Camera::Camera(const glm::vec3 &pos, const float pitch, const float yaw)
	: position(pos), speed(0.f, 0.f, 0.f), pitch(pitch), yaw(yaw), moveForward(0), moveRight(0), moveTop(0)
{}

void Camera::tick()
{
	speed += getDirection() * (moveForward * CAMERA_SPEED);
	speed += getRight() * (moveRight * CAMERA_SPEED);
	speed += getTop() * (moveTop * CAMERA_SPEED);
	speed *= CAMERA_DRAG;
	position += speed;
}

void Camera::stop()
{
	moveForward = 0;
	moveRight = 0;
	moveTop = 0;
}

glm::vec3 Camera::getUp() const
{
	return glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec3 Camera::getRight() const
{
	return glm::normalize(glm::cross(getDirection(), getUp()));
}

glm::vec3 Camera::getDirection() const
{
	return glm::vec3(
		cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
		sin(glm::radians(pitch)),
		cos(glm::radians(pitch)) * sin(glm::radians(yaw))
	);
}

glm::vec3 Camera::getTop() const
{
	return glm::normalize(glm::cross(getRight(), getDirection()));
}

glm::mat4 Camera::getLookAt() const
{
	return glm::lookAt(position, position + getDirection(), getUp());
}

glm::vec3 Camera::getPosition() const
{
	return position;
}

void Camera::captureMouse()
{
	MouseManager::capture(this);
}

void Camera::captureKeyboard()
{
	KeyboardManager::capture(this);
}

void Camera::onMouseMoved(glm::vec2 diff)
{
	yaw += diff.x * CAMERA_ROTATE_SPEED;
	pitch -= diff.y * CAMERA_ROTATE_SPEED;
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}
}

void Camera::onKeyPressed(const int key)
{
	switch (key)
	{
		case GLFW_KEY_W:
			moveForward++;
			break;
		case GLFW_KEY_S:
			moveForward--;
			break;
		case GLFW_KEY_A:
			moveRight--;
			break;
		case GLFW_KEY_D:
			moveRight++;
			break;
		case GLFW_KEY_SPACE:
			moveTop++;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			moveTop--;
			break;
		case GLFW_KEY_R:
			printStats();
			break;
		default:
			break;
	}
}

void Camera::onKeyReleased(const int key)
{
	switch (key)
	{
		case GLFW_KEY_W:
			moveForward--;
			break;
		case GLFW_KEY_S:
			moveForward++;
			break;
		case GLFW_KEY_A:
			moveRight++;
			break;
		case GLFW_KEY_D:
			moveRight--;
			break;
		case GLFW_KEY_SPACE:
			moveTop--;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			moveTop++;
			break;
		default:
			break;
	}
}

void Camera::printStats() const {
	std::cout << "position=(" << position.x << "," << position.y << "," << position.z << ")\n"
			  << "yaw=" << yaw << "  pitch=" << pitch << std::endl;
}
