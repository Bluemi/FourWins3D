#include "BlockRow.hpp"

BlockRow::BlockRow(const vec3i &step)
	: step(step)
{}

void BlockRow::buildFrom(const vec3i &pos, BlockContainer *container)
{
	vec3i position = pos;
	while (container->inScope(pos))
	{
		blocks.push_back(container->get(position));
		position = position + step;
	}
}

BlockType BlockRow::hasWinnerRow(const unsigned int limit, std::vector<Entity*> &winnerEntities)
{
	BlockType t;
	bool winnerFound = false;
	for (Entity* e : blocks)
	{
		if (e == nullptr)
		{
			t = BlockType::NONE;
			winnerEntities.clear();
		} else if (e->getBlockType() == t) {
			winnerEntities.push_back(e);
			if (winnerEntities.size() >= limit)
			{
				winnerFound = true;
				break;
			}
		} else if (e->getBlockType() != t) {
			t = e->getBlockType();
			winnerEntities.clear();
			winnerEntities.push_back(e);
		}
	}
	if (!winnerFound)
		t = BlockType::NONE;
	return t;
}
