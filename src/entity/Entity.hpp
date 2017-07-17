#ifndef __ENTITY_CLASS__
#define __ENTITY_CLASS__

#include <glm/glm.hpp>

#include <texture/Texture.hpp>
#include <shape/Shape.hpp>

class Entity
{
	public:
		Entity(const glm::vec3 &position, const glm::vec3 color, Shape *shape, Texture *texture);

		glm::mat4 getModel() const;
		glm::vec3 getColor() const;
		Texture *getTexture() const;
		Shape *getShape() const;
	private:
		glm::mat4 model;
		glm::vec3 color;
		Shape *shape;
		Texture *texture;
};

#endif
