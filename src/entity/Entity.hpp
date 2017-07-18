#ifndef __ENTITY_CLASS__
#define __ENTITY_CLASS__

#include <glm/glm.hpp>

#include <texture/Texture.hpp>
#include <shape/Shape.hpp>
#include <game/container/BlockType.hpp>

class Entity
{
	public:
		Entity(const glm::vec3 &position, const BlockType &type, Shape *shape, Texture *texture);

		glm::mat4 getModel() const;
		BlockType getBlockType() const;
		Texture *getTexture() const;
		Shape *getShape() const;
	private:
		glm::mat4 model;
		BlockType blockType;
		Shape *shape;
		Texture *texture;
};

#endif
