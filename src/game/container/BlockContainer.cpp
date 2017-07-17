#include "BlockContainer.hpp"

BlockContainer::BlockContainer()
{
}

bool BlockContainer::isBlockThere(const int x, const int y, const int z)
{
	if (blocks.find(x) == blocks.end())
		return false;
	if (blocks[x].find(y) == blocks[x].end())
		return false;
	return (blocks[x][y].find(z) != blocks[x][y].end());
}

bool BlockContainer::insert(const int x, const int y, const int z, Entity* block)
{
	if (!isBlockThere(x, y, z))
	{
		blocks[x][y][z] = block;
		blockList.push_back(block);
		return true;
	}
	return false;
}

Entity* BlockContainer::get(const int x, const int y, const int z)
{
	if (!isBlockThere(x, y, z))
	{
		return nullptr;
	}
	return blocks[x][y][z];
}

const std::vector<Entity*>& BlockContainer::getList() const
{
	return blockList;
}
