#ifndef __BLOCKSTATE_CLASS__
#define __BLOCKSTATE_CLASS__

#include <glm/glm.hpp>

struct BlockState
{
	vec3i blockIndex;
	glm::vec3 position;
	glm::vec3 direction;

	BlockState(const glm::vec3 &pos, const glm::vec3 &dir)
		: blockIndex(round(pos.x), round(pos.y), round(pos.z))
	{
		position = pos;
		direction = dir;
	}

	glm::vec3 getTarget()
	{
		glm::vec3 target;
		for (int i = 0; i < 3; i++)
		{
			if (direction[i] > 0.0f) {
				target[i] = blockIndex[i] + 0.5f;
			} else if (direction[i] < 0.0f) {
				target[i] = blockIndex[i] - 0.5f;
			} else {
				target[i] = INFINITY;
			}
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
				blockIndex.x += (direction.x > 0.0f)?1:-1;
			}
			else
			{
				minDuration = duration.z;
				blockIndex.z += (direction.z > 0.0f)?1:-1;
			}
		} else {
			if (duration.y < duration.z)
			{
				minDuration = duration.y;
				blockIndex.y += (direction.y > 0.0f)?1:-1;
			}
			else
			{
				minDuration = duration.z;
				blockIndex.z += (direction.z > 0.0f)?1:-1;
			}
		}
		position += minDuration * direction;
	}
};

#endif
