#include "sprite_sheet.h"

SpriteSheet::SpriteSheet(const std::string &path, Window &window,
			 const int clip_width, const int clip_height,
			 const int margin) {
	texture.from_image(path, window);
	this->clip_width = clip_width;
	this->clip_height = clip_height;
	this->margin = margin;
	all.set_dimensions(texture.get_width(), texture.get_height());
	set_cells(Order::RowMajor);
}

SpriteSheet::SpriteSheet(const std::string &path, Window &window,
			 const int clip_width, const int clip_height) {
	texture.from_image(path, window);
	this->clip_width = clip_width;
	this->clip_height = clip_height;
	margin = 0;
	all.set_dimensions(texture.get_width(), texture.get_height());
	set_cells(Order::RowMajor);
}

SpriteSheet &SpriteSheet::operator=(const SpriteSheet &copy) {
	clip_width = copy.clip_width;
	clip_height = copy.clip_height;
	margin = copy.margin;
	texture = copy.texture;
	cells = copy.cells;
	all = copy.all;
	return *this;
}

void SpriteSheet::set_cells(const Order order) {
	int x = 0, y = 0;
	if (order == Order::RowMajor) {
		for (int i = clip_height; i <= texture.get_height();
		     i += (clip_height + margin)) {
			for (int j = clip_width; j <= texture.get_width();
			     j += (clip_width + margin)) {
				if (x == texture.get_width()) {
					x = 0;
					y += (clip_height + margin);
				}
				cells.push_back(
				    Rect(x, y, clip_width, clip_height));
				x += (clip_width + margin);
			}
		}
	} else {
		for (int i = clip_width; i <= texture.get_width();
		     i += (clip_width + margin)) {
			for (int j = clip_height; j <= texture.get_height();
			     j += (clip_height + margin)) {
				if (x == texture.get_width()) {
					x = 0;
					y += (clip_height + margin);
				}
				cells.push_back(
				    Rect(x, y, clip_width, clip_height));
				x += (clip_width + margin);
			}
		}
	}
}
