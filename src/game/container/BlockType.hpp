#ifndef __BLOCKTYPE_ENUM__
#define __BLOCKTYPE_ENUM__

enum BlockType
{
	NONE, RED, YELLOW
};

BlockType nextType(BlockType t)
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

#endif
