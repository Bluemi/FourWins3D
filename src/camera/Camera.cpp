#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <math.h>

#include <interaction/MouseManager.hpp>

Camera::Camera(const glm::vec3 &pos, const float pitch, const float yaw)
	: position(pos), pitch(pitch), yaw(yaw)
{}

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

glm::mat4 Camera::getLookAt() const
{
	return glm::lookAt(position, position + getDirection(), getUp());
}

void Camera::captureMouse()
{
	MouseManager::capture(this);
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

void Camera::goForward()
{
	position += getDirection() * camSpeed;
}

void Camera::goBackward()
{
	position -= getDirection() * camSpeed;
}

void Camera::goLeft()
{
	position -= getRight() * camSpeed;
}

void Camera::goRight()
{
	position += getRight() * camSpeed;
}
