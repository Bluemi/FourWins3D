#include "KeyboardManager.hpp"

KeyboardListener *KeyboardManager::listener;
GLFWwindow *KeyboardManager::window;
std::vector<KeyboardManager::KeyboardKey> KeyboardManager::keys;

void KeyboardManager::init(GLFWwindow *w)
{
	window = w;
	keys.push_back(KeyboardKey(GLFW_KEY_W));
	keys.push_back(KeyboardKey(GLFW_KEY_A));
	keys.push_back(KeyboardKey(GLFW_KEY_S));
	keys.push_back(KeyboardKey(GLFW_KEY_D));
	keys.push_back(KeyboardKey(GLFW_KEY_SPACE));
	keys.push_back(KeyboardKey(GLFW_KEY_LEFT_CONTROL));

	listener = nullptr;
}

void KeyboardManager::capture(KeyboardListener *l)
{
	listener = l;
}

void KeyboardManager::call()
{
	for (KeyboardKey &k : keys)
	{
		if (k.pressed != (glfwGetKey(window, k.key) == GLFW_PRESS))
		{
			k.pressed = (glfwGetKey(window, k.key) == GLFW_PRESS);
			if (listener != nullptr)
			{
				if (k.pressed)
				{
					listener->onKeyPressed(k.key);
				} else {
					listener->onKeyReleased(k.key);
				}
			}
		}
	}
}

bool KeyboardManager::isKeyPressed(const int key)
{
	return (glfwGetKey(window, key) == GLFW_PRESS);
}
