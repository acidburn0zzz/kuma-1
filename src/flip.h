#ifndef _FLIP_H_
#define _FLIP_H_

#include <SDL.h>

#include "SDL_render.h"

enum Flip {
	None = SDL_FLIP_NONE,
	Horizontal = SDL_FLIP_HORIZONTAL,
	Vertical = SDL_FLIP_VERTICAL,
	Diagonal = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL,
};

class Flippable {
public:
	Flippable() {}
	Flip &get_orientation();
	void orientation_reset();
	void flip(Flip orientation);
	void flip_horizontal();
	void flip_vertical();
	void flip_diagonal();

private:
	Flip orientation = Flip::None;
};

#endif
