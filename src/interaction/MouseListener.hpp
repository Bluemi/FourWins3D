#ifndef __MOUSELISTENER_CLASS__
#define __MOUSELISTENER_CLASS__

#include <glm/glm.hpp>

class MouseListener
{
	public:
		virtual void onMouseMoved(glm::vec2 diff) = 0;
};

#endif
