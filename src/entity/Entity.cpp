#include "Entity.hpp"

#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(const glm::vec3 &position, const BlockType &type, Shape* shape, Texture *texture)
	: blockType(type), shape(shape), texture(texture)
{
	model = glm::translate(model, position);
}

glm::mat4 Entity::getModel() const
{
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
