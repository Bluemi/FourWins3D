#ifndef __KEYBOARDLISTENER_CLASS__
#define __KEYBOARDLISTENER_CLASS__

class KeyboardListener
{
	public:
		virtual void onKeyPressed(const int key) = 0;
		virtual void onKeyReleased(const int key) = 0;
};

#endif
