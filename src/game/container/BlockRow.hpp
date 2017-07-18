#ifndef __BLOCKROW_CLASS__
#define __BLOCKROW_CLASS__

#include <vector>

#include "BlockType.hpp"

class BlockRow
{
	public:
		BlockRow(short xStep, short yStep, short zStep);
		void nextStep();
		short getxStep() const;
		short getyStep() const;
		short getzStep() const;
		void addBlock(BlockType b);
	private:
		std::vector<BlockType> blocks;
		short xStep;
		short yStep;
		short zStep;
};

#endif
