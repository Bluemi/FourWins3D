#include "BlockContainer.hpp"

#include <math.h>
#include <iostream>

#include <debug/Debug.hpp>

BlockContainer::BlockContainer()
	: minX(0), maxX(0), minY(0), maxY(0), minZ(0), maxZ(0)
{}

bool BlockContainer::inScope(const int x, const int y, const int z)
{
	if (x < minX)
		return false;
	if (x > maxX)
		return false;

	if (y < minY)
		return false;
	if (y > maxY)
		return false;

	if (z < minZ)
		return false;
	if (z > maxZ)
		return false;
	return true;
}

bool BlockContainer::isBlockThere(const int x, const int y, const int z)
{
	if (!inScope(x, y, z))
		return false;

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
		minX = std::min(x, minX);
		maxX = std::max(x, maxX);
		minY = std::min(y, minY);
		maxY = std::max(y, maxY);
		minZ = std::min(z, minZ);
		maxZ = std::max(z, maxZ);
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

struct BlockState
{
	int xBlock;
	int yBlock;
	int zBlock;
	glm::vec3 position;
	glm::vec3 direction;

	BlockState(const glm::vec3 &pos, const glm::vec3 &dir)
	{
		xBlock = round(pos.x);
		yBlock = round(pos.y);
		zBlock = round(pos.z);
		position = pos;
		direction = dir;
	}

	glm::vec3 getTarget()
	{
		glm::vec3 target;
		if (direction.x > 0.0f) {
			target.x = xBlock + 0.5f;
		} else if (direction.x < 0.0f) {
			target.x = xBlock - 0.5f;
		} else {
			target.x = INFINITY;
		}
		if (direction.y > 0.0f) {
			target.y = yBlock + 0.5f;
		} else if (direction.y < 0.0f) {
			target.y = yBlock - 0.5f;
		} else {
			target.y = INFINITY;
		}
		if (direction.z > 0.0f) {
			target.z = zBlock + 0.5f;
		} else if (direction.z < 0.0f) {
			target.z = zBlock - 0.5f;
		} else {
			target.z = INFINITY;
		}
		return target;
	}

	void nextStep()
	{
		glm::vec3 target = getTarget();
		glm::vec3 step = target - position;
		glm::vec3 duration = step / direction;
		float minDuration;
		if (duration.x < duration.y)
		{
			if (duration.x < duration.z)
			{
				minDuration = duration.x;
				xBlock += (direction.x > 0.0f)?1:-1;
			}
			else
			{
				minDuration = duration.z;
				zBlock += (direction.z > 0.0f)?1:-1;
			}
		} else {
			if (duration.y < duration.z)
			{
				minDuration = duration.y;
				yBlock += (direction.y > 0.0f)?1:-1;
			}
			else
			{
				minDuration = duration.z;
				zBlock += (direction.z > 0.0f)?1:-1;
			}
		}
		position += minDuration * direction;
	}
};

bool BlockContainer::canPlaceBlockHere(const glm::vec3 &camPosition, const glm::vec3 &camDir, glm::vec3 &newPosition)
{
	BlockState state(camPosition, camDir);
	BlockState lastState(state);
	bool inScope = true;
	bool wasInScope = false;
	bool found = false;
	int counter = 0;
	while (inScope && !found && (counter < 2000))
	{
		counter++;
		if (isBlockThere(state.xBlock, state.yBlock, state.zBlock))
		{
			newPosition.x = lastState.xBlock;
			newPosition.y = lastState.yBlock;
			newPosition.z = lastState.zBlock;
			found = true;
		} else {
			lastState = state;
			if (this->inScope(state.xBlock, state.yBlock, state.zBlock)) // in scope
			{
				wasInScope = true;
			}
			else
			{
				if (wasInScope)
					inScope = false;
			}
			state.nextStep();
		}
	}
	return found;
}
