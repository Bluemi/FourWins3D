#ifndef __CROSSSHAPE_CLASS__
#define __CROSSSHAPE_CLASS__

#include "Shape.hpp"

class CrossShape : public Shape
{
	public:
		CrossShape();
		virtual void load() override;
		virtual void defineVertexAttribPointer() const override;
};

#endif
