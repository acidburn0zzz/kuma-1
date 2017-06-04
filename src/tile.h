#ifndef _TILE_H_
#define _TILE_H_

#include <string>

#include "drawable.h"
#include "rect.h"
#include "texture.h"

class Window;

class Tile : public Drawable {
public:
	Tile(std::string, Window &window, int, int);
	Tile(Texture &texture, int, int);
	Texture texture;
	Rect rect;
	void draw(Window &window);
};

#endif // _TILE_H_
