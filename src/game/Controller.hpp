#ifndef __CONTROLLER_CLASS__
#define __CONTROLLER_CLASS__

#include <interaction/KeyboardListener.hpp>

class Game;

class Controller : public KeyboardListener
{
	public:
		Controller();
		void init(Game *game);
		virtual void onKeyPressed(int key) override;
		virtual void onKeyReleased(int key) override;
	private:
		Game *game;
};

#include "Game.hpp"

#endif
