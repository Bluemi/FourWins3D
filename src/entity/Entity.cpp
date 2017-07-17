#include "Entity.hpp"

#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(const glm::vec3 &position, const glm::vec3 color, Shape* shape, Texture *texture)
	: color(color), shape(shape), texture(texture)
{
	model = glm::translate(model, position);
}

glm::mat4 Entity::getModel() const
{
	return model;
}

glm::vec3 Entity::getColor() const
{
	return color;
}

Texture *Entity::getTexture() const
{
	return texture;
}

Shape *Entity::getShape() const
{
	return shape;
}
