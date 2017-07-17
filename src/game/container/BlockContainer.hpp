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
		bool inScope(const int x, const int y, const int z);
		bool isBlockThere(const int x, const int y, const int z);
		bool insert(const int x, const int y, const int z, Entity* block);
		const std::vector<Entity*>& getList() const;
		Entity* get(const int x, const int y, const int z);
		bool canPlaceBlockHere(const glm::vec3 &camPosition, const glm::vec3 &camDir, glm::vec3 &newPosition);
	private:
		std::map<int, std::map<int, std::map<int, Entity*>>> blocks;
		std::vector<Entity*> blockList;
		int minX;
		int maxX;
		int minY;
		int maxY;
		int minZ;
		int maxZ;
};

#endif
