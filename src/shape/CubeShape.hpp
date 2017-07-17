#ifndef __CUBESHAPE_CLASS__
#define __CUBESHAPE_CLASS__

#include "Shape.hpp"

class CubeShape : public Shape
{
	public:
		CubeShape();
		virtual void load() override;
		virtual void defineVertexAttribPointer() const override;
		virtual std::vector<Plane> getPlanes() const override;
};

#endif
