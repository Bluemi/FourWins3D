#include "BlockType.hpp"

BlockType nextBlockType(BlockType t)
{
	BlockType res;
	switch (t)
	{
		case BlockType::NONE:
			res = BlockType::NONE;
			break;
		case BlockType::RED:
			res = BlockType::YELLOW;
			break;
		case BlockType::YELLOW:
			res = BlockType::RED;
			break;
		default:
			res = BlockType::NONE;
			break;
	}
	return res;
}

glm::vec3 toColor(const BlockType type)
{
	glm::vec3 c(0.f);
	switch (type)
	{
		case BlockType::NONE:
			c = glm::vec3(0.5f, 0.5f, 0.5f);
			break;
		case BlockType::RED:
			c = glm::vec3(0.6f, 0.1f, 0.1f);
			break;
		case BlockType::YELLOW:
			c = glm::vec3(0.5f, 0.5f, 0.1f);
			break;
	}
	return c;
}
