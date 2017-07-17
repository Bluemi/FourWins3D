#ifndef __BLOCKCONTAINER_CLASS__
#define __BLOCKCONTAINER_CLASS__

#include <map>
#include <vector>

#include <entity/Entity.hpp>

class Entity;

class BlockContainer
{
	public:
		BlockContainer();
		bool isBlockThere(const int x, const int y, const int z);
		bool insert(const int x, const int y, const int z, Entity* block);
		const std::vector<Entity*>& getList() const;
		Entity* get(const int x, const int y, const int z);
	private:
		std::map<int, std::map<int, std::map<int, Entity*>>> blocks;
		std::vector<Entity*> blockList;
};

#endif
