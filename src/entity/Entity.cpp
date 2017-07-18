#include "Entity.hpp"

#include <stdlib.h>

#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(const glm::vec3 &position, const BlockType &type, Shape* shape, Texture *texture)
	: blockType(type), shape(shape), texture(texture), position(position), rotation(0.0f), spin(0.0f)
{}

glm::mat4 Entity::getModel() const
{
	glm::mat4 model;
	model = glm::translate(model, position);
	if (rotation != 0.0f)
		model = glm::rotate(model, rotation, speed);
	return model;
}

BlockType Entity::getBlockType() const
{
	return blockType;
}

Texture *Entity::getTexture() const
{
	return texture;
}

Shape *Entity::getShape() const
{
	return shape;
}

void Entity::winner()
{
	win = true;
}

void Entity::randomShit()
{
	if (!win)
	{
		spin = ((rand() % 10) - 5) * 0.01f;
		speed.x = ((rand() % 10) - 5) * 0.005f;
		speed.y = ((rand() % 10) - 5) * 0.005f;
		speed.z = ((rand() % 10) - 5) * 0.005f;
	}
}

void Entity::tick()
{
	rotation += spin;
	position += speed;
}
