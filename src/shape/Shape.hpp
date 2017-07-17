#ifndef __SHAPE_CLASS__
#define __SHAPE_CLASS__

#include <vector>

class Shape
{
	public:
		Shape();
		virtual ~Shape();
		virtual void load() = 0;
		virtual void defineVertexAttribPointer() const = 0;
		void use() const;
		static void unuse();
	protected:
		void applyVertices(const void *vertices, const unsigned int size);
	private:
		unsigned int VAO;
		unsigned int VBO;
};

#endif
