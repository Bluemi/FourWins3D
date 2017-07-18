#ifndef __BLOCKROW_CLASS__
#define __BLOCKROW_CLASS__

#include <vector>

#include "BlockContainer.hpp"
#include <entity/Entity.hpp>

class BlockRow
{
	public:
		BlockRow(const vec3i &step);
		vec3i getStep() const;
		void buildFrom(const vec3i &pos, BlockContainer *container);
		BlockType hasWinnerRow(const unsigned int limit, std::vector<Entity*> &winnerEntities);
	private:
		std::vector<Entity*> blocks;
		vec3i step;
};

#endif
