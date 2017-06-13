#ifndef _SPRITE_SHEET_H_
#define _SPRITE_SHEET_H_

#include <deque>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "rect.h"
#include "texture.h"

namespace kuma {
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
		int clip_width() const;
		int clip_height() const;
		int clip_margin() const;
		SpriteSheet &operator=(const SpriteSheet &copy);
		Texture texture;
		std::vector<Rect> cells;
		Rect all;
	private:
		int clip_height_;
		int clip_width_;
		int margin_;
	};
}

#endif // _SPRITE_SHEET_H_
