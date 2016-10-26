#ifndef _KEY_INPUT_H_
#define _KEY_INPUT_H_

#include <SDL.h>

class KeyInput {
public:
	KeyInput() {}
	bool key_pressed(SDL_Keycode &key);
	bool key_released(SDL_Keycode &key);

private:
	SDL_Event event;
};

#endif
