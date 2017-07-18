#ifndef __BLOCKCONTAINER_CLASS__
#define __BLOCKCONTAINER_CLASS__

#include <map>
#include <vector>

#include <entity/Entity.hpp>
#include <math/vec3i.hpp>

class Entity;

class BlockContainer
{
	public:
		BlockContainer();
		bool inScope(const vec3i &index);
		bool isBlockThere(const vec3i &index);
		bool insert(const vec3i &index, Entity* block);
		const std::vector<Entity*>& getList() const;
		Entity* get(const vec3i &index);
		bool canPlaceBlockHere(const glm::vec3 &camPosition, const glm::vec3 &camDir, vec3i &newPosition);
	private:
		std::map<int, std::map<int, std::map<int, Entity*>>> blocks;
		std::vector<Entity*> blockList;
		vec3i minIndex;
		vec3i maxIndex;
};

#endif
