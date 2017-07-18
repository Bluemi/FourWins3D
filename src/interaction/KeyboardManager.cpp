#include "KeyboardManager.hpp"

std::vector<KeyboardListener*> KeyboardManager::listeners;
GLFWwindow *KeyboardManager::window;
std::vector<KeyboardManager::KeyboardKey> KeyboardManager::keys;

void KeyboardManager::init(GLFWwindow *w)
{
	window = w;
	keys.push_back(KeyboardKey(GLFW_KEY_W));
	keys.push_back(KeyboardKey(GLFW_KEY_A));
	keys.push_back(KeyboardKey(GLFW_KEY_S));
	keys.push_back(KeyboardKey(GLFW_KEY_D));
	keys.push_back(KeyboardKey(GLFW_KEY_E));
	keys.push_back(KeyboardKey(GLFW_KEY_R));
	keys.push_back(KeyboardKey(GLFW_KEY_SPACE));
	keys.push_back(KeyboardKey(GLFW_KEY_LEFT_CONTROL));
}

void KeyboardManager::capture(KeyboardListener *l)
{
	listeners.push_back(l);
}

void KeyboardManager::uncapture(KeyboardListener *l)
{
	for (auto iter = listeners.begin(); iter != listeners.end(); ++iter)
	{
		if (*iter == l)
		{
			listeners.erase(iter);
		}
	}
}

void KeyboardManager::call()
{
	for (KeyboardKey &k : keys)
	{
		if (k.pressed != (glfwGetKey(window, k.key) == GLFW_PRESS))
		{
			k.pressed = (glfwGetKey(window, k.key) == GLFW_PRESS);
			for (KeyboardListener *listener : listeners)
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
