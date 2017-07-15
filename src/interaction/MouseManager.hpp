#ifndef __MOUSEMANAGER_CLASS__
#define __MOUSEMANAGER_CLASS__

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <interaction/MouseListener.hpp>

class MouseManager
{
	public:
		static void init(GLFWwindow *window);
		static void call();
		static void capture(MouseListener *listener);
	private:
		static void mouseCallback(GLFWwindow *window, double x, double y);
		MouseManager();
		static MouseListener *listener;
		static glm::vec2 current;
		static glm::vec2 last;
		static bool hasGotFirstPosition;
};

#endif
