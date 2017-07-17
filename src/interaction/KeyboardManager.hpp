#ifndef __KEYBOARDMANAGER_CLASS__
#define __KEYBOARDMANAGER_CLASS__

#include <GLFW/glfw3.h>
#include <vector>

#include "KeyboardListener.hpp"

class KeyboardManager
{
	struct KeyboardKey
	{
		KeyboardKey(int k, bool p = false)
			: key(k), pressed(p)
		{}
		int key;
		bool pressed;
	};
	public:
		static void init(GLFWwindow *w);
		static void capture(KeyboardListener *l);
		static void uncapture(KeyboardListener *l);
		static bool isKeyPressed(const int key);
		static void call();
	private:
		KeyboardManager();

		static std::vector<KeyboardListener*> listeners;
		static GLFWwindow *window;
		static std::vector<KeyboardKey> keys;
};

#endif
