#ifndef __BLOCKTYPE_ENUM__
#define __BLOCKTYPE_ENUM__

#include <glm/glm.hpp>

enum BlockType
{
	NONE, RED, YELLOW
};

BlockType nextBlockType(BlockType t);
glm::vec3 toColor(const BlockType);

#endif
