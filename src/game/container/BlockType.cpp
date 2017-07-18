#include "BlockType.hpp"

BlockType nextBlockType(BlockType t)
{
	BlockType res;
	switch (t)
	{
		case BlockType::NONE:
			res = BlockType::NONE;
		case BlockType::RED:
			res = BlockType::YELLOW;
		case BlockType::YELLOW:
			res = BlockType::RED;
		default:
			res = BlockType::NONE;
	}
	return res;
}

glm::vec3 toColor(const BlockType type)
{
	glm::vec3 c;
	switch (type)
	{
		case BlockType::NONE:
			c = glm::vec3(0, 0, 0);
			break;
		case BlockType::RED:
			c = glm::vec3(0.7f, 0.1f, 0.1f);
			break;
		case BlockType::YELLOW:
			c = glm::vec3(0.5f, 0.5f, 0.1f);
			break;
	}
	return c;
}
