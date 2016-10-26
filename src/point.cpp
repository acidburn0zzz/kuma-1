#include "point.h"

Point::Point(const int x, const int y) { set_position(x, y); }

void Point::set_x_cord(const int x) { inner.x = x; }

void Point::set_y_cord(const int y) { inner.y = y; }

void Point::set_position(const int x, const int y) {
	inner.x = x;
	inner.y = y;
}

int Point::get_x_cord() const { return inner.x; }

int Point::get_y_cord() const { return inner.y; }

SDL_Point &Point::get_sdl_point() {
	return inner;
}
