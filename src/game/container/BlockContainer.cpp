#include "BlockContainer.hpp"

#include <math.h>
#include <iostream>

#include <misc/Debug.hpp>
#include "BlockState.hpp"
#include "BlockRow.hpp"

const int BlockContainer::WINNER_LIMIT = 5;

BlockContainer::BlockContainer()
{}

BlockContainer::~BlockContainer()
{
	clearAndDelete();
}

void BlockContainer::clearAndDelete()
{
	for (Entity* e : blockList)
	{
		delete e;
	}
	blockList.clear();
	blocks.clear();
}

bool BlockContainer::inScope(const vec3i &index)
{
	return (index >= minIndex) && (index <= maxIndex);
}

bool BlockContainer::isBlockThere(const vec3i &index)
{
	if (!inScope(index))
		return false;

	if (blocks.find(index.x) == blocks.end())
		return false;
	if (blocks[index.x].find(index.y) == blocks[index.x].end())
		return false;
	return (blocks[index.x][index.y].find(index.z) != blocks[index.x][index.y].end());
}

bool BlockContainer::insert(const vec3i &index, Entity* block)
{
	if (!isBlockThere(index))
	{
		blocks[index.x][index.y][index.z] = block;
		blockList.push_back(block);
		minIndex = minIndex.min(index);
		maxIndex = maxIndex.max(index);
		return true;
	}
	return false;
}

Entity* BlockContainer::get(const vec3i &index)
{
	if (!isBlockThere(index))
	{
		return nullptr;
	}
	return blocks[index.x][index.y][index.z];
}

const std::vector<Entity*>& BlockContainer::getList() const
{
	return blockList;
}

bool BlockContainer::canPlaceBlockHere(const glm::vec3 &camPosition, const glm::vec3 &camDir, vec3i &newPosition)
{
	BlockState state(camPosition, camDir);
	BlockState lastState(state);
	bool inScope = true;
	if (isBlockThere(state.blockIndex))
	{
		inScope = false;
	}
	bool wasInScope = false;
	bool found = false;
	int counter = 0;
	while (inScope && !found && (counter < 2000))
	{
		counter++;
		if (isBlockThere(state.blockIndex))
		{
			newPosition = lastState.blockIndex;
			found = true;
		} else {
			lastState = state;
			if (this->inScope(state.blockIndex)) // in scope
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

bool BlockContainer::checkWinner(const vec3i &position, std::vector<Entity*> &winnerEntities)
{
	for (int x = -1; x <= 1; x++)
	for (int y = -1; y <= 1; y++)
	for (int z = -1; z <= 1; z++)
	{
		if (x || y || z)
		{
			BlockRow row(vec3i(x, y, z));
			row.buildFrom(position, this, WINNER_LIMIT);
			if (row.hasWinnerRow(WINNER_LIMIT, winnerEntities) != BlockType::NONE)
			{
				return true;
			}
		}
	}
	return false;
}

void BlockContainer::tick()
{
	for (Entity* e : blockList)
	{
		e->tick();
	}
}

void BlockContainer::randomShit()
{
	for (Entity* e : blockList)
	{
		e->randomShit();
	}
}
