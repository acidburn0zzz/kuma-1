#ifndef _TILE_H_
#define _TILE_H_

#include "rect.h"
#include "texture.h"
#include "window.h"

class Tile {
public:
	Tile(std::string, Window &window, int, int);
	Tile(Texture &texture, int, int);
	Texture texture;
	Rect rect;
};

#endif // _TILE_H_
