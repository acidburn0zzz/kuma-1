#include "sprite_sheet.h"

using namespace kuma;
class Window;

SpriteSheet::SpriteSheet(const std::string &path, Window &window,
			 const int clip_width, const int clip_height,
			 const int margin) {
	texture.from_image(path, window);
	this->clip_width_ = clip_width;
	this->clip_height_ = clip_height;
	this->margin_ = margin;
	all.set_dimensions(texture.get_width(), texture.get_height());
	set_cells(Order::RowMajor);
}

SpriteSheet::SpriteSheet(const std::string &path, Window &window,
			 const int clip_width, const int clip_height) {
	texture.from_image(path, window);
	this->clip_width_ = clip_width;
	this->clip_height_ = clip_height;
	margin_ = 0;
	all.set_dimensions(texture.get_width(), texture.get_height());
	set_cells(Order::RowMajor);
}

SpriteSheet &SpriteSheet::operator=(const SpriteSheet &copy) {
	clip_width_ = copy.clip_width_;
	clip_height_ = copy.clip_height_;
	margin_ = copy.margin_;
	texture = copy.texture;
	cells = copy.cells;
	all = copy.all;
	return *this;
}

void SpriteSheet::set_cells(const Order order) {
	int x = 0, y = 0;
	if (order == Order::RowMajor) {
		for (int i = clip_height_; i <= texture.get_height();
		     i += (clip_height_ + margin_)) {
			for (int j = clip_width_; j <= texture.get_width();
			     j += (clip_width_ + margin_)) {
				if (x == texture.get_width()) {
					x = 0;
					y += (clip_height_ + margin_);
				}
				cells.push_back(
				    Rect(x, y, clip_width_, clip_height_));
				x += (clip_width_ + margin_);
			}
		}
	} else {
		for (int i = clip_width_; i <= texture.get_width();
		     i += (clip_width_ + margin_)) {
			for (int j = clip_height_; j <= texture.get_height();
			     j += (clip_height_ + margin_)) {
				if (x == texture.get_width()) {
					x = 0;
					y += (clip_height_ + margin_);
				}
				cells.push_back(
				    Rect(x, y, clip_width_, clip_height_));
				x += (clip_width_ + margin_);
			}
		}
	}
}

int SpriteSheet::clip_width() const { return clip_width_; }

int SpriteSheet::clip_height() const { return clip_height_; }

int SpriteSheet::clip_margin() const { return margin_; }
