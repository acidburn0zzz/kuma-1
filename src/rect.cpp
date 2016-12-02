#include "rect.h"
#include "window.h"

Rect::Rect() {
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	x_velocity = 0;
	y_velocity = 0;
	set_outline_color(255, 0, 0, 0);
}

Rect::Rect(int w, int h) {
	rect.x = 0;
	rect.y = 0;
	rect.w = w;
	rect.h = h;
	x_velocity = 0;
	y_velocity = 0;
	set_outline_color(255, 0, 0, 0);
}

Rect::Rect(int x, int y, int w, int h) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	x_velocity = 0;
	y_velocity = 0;
	set_outline_color(255, 0, 0, 0);
}

SDL_Rect *Rect::get_sdl_rect() { return &rect; }

void Rect::draw(Window &window) {
	SDL_SetRenderDrawColor(window.get_renderer(), rect_color.r,
			       rect_color.g, rect_color.b, rect_color.a);
	SDL_RenderDrawRect(window.get_renderer(), &rect);
	SDL_SetRenderDrawColor(window.get_renderer(), 0x00, 0x00, 0x00, 0x00);
}

void Rect::set_outline_color(const uint8_t R, const uint8_t G, const uint8_t B,
			     const uint8_t A) {
	rect_color.r = R;
	rect_color.g = G;
	rect_color.b = B;
	rect_color.a = A;
}

void Rect::reset_position() {
	rect.x = 0;
	rect.y = 0;
}

void Rect::set_position(const int x, const int y) {
	rect.x = x;
	rect.y = y;
}

void Rect::set_position(const std::tuple<int, int> pos) {
	rect.x = std::get<0>(pos);
	rect.y = std::get<1>(pos);
}

int Rect::get_x_cord() { return rect.x; }

int Rect::get_y_cord() { return rect.y; }

void Rect::set_x_cord(const int x) { rect.x = x; }

void Rect::set_y_cord(const int y) { rect.y = y; }

std::tuple<int, int> Rect::get_position() const {
	return std::make_tuple(rect.x, rect.y);
}

int Rect::get_width() { return rect.w; }

int Rect::get_height() { return rect.h; }

void Rect::set_width(const int w) { rect.w = w; }

void Rect::set_height(const int h) { rect.h = h; }

std::tuple<int, int> Rect::get_dimensions() {
	return std::make_tuple(rect.w, rect.h);
}

void Rect::set_dimensions(const std::tuple<int, int> dim) {
	rect.w = std::get<0>(dim);
	rect.h = std::get<1>(dim);
}

void Rect::set_dimensions(const int w, const int h) {
	rect.w = w;
	rect.h = h;
}

Rect &Rect::operator=(const Rect &copy) {
	rect = copy.rect;
	x = copy.x;
	y = copy.y;
	w = copy.w;
	h = copy.h;
	rect_color = copy.rect_color;
	return *this;
}

void Rect::set_velocities(const int x, const int y) {
	x_velocity = x;
	y_velocity = y;
}

void Rect::set_x_velocity(const int x) { x_velocity = x; }

void Rect::set_y_velocity(const int y) { y_velocity = y; }

int Rect::get_x_velocity() const { return x_velocity; }

int Rect::get_y_velocity() const { return y_velocity; }
