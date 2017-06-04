#ifndef _SPRITE_SHEET_H_
#define _SPRITE_SHEET_H_

#include <deque>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "rect.h"
#include "texture.h"

class Window;

enum class Order {
	RowMajor,
	ColumnMajor,
};

class SpriteSheet {
public:
	SpriteSheet() {}
	SpriteSheet(const std::string &path, Window &window,
		    const int clip_width, const int clip_height,
		    const int margin);
	SpriteSheet(const std::string &path, Window &window,
		    const int clip_width, const int clip_height);
	void set_cells(const Order order);
	int clip_height;
	int clip_width;
	int margin;
	SpriteSheet &operator=(const SpriteSheet &copy);
	Texture texture;
	std::vector<Rect> cells;
	Rect all;
};

#endif // _SPRITE_SHEET_H_
