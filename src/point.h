#ifndef _POINT_H_
#define _POINT_H_

#include <SDL.h>

#include "SDL_rect.h"

namespace kuma {
	class Point {
	public:
		Point(const int x, const int y);
		void set_x_cord(const int x);
		void set_y_cord(const int y);
		int get_x_cord() const;
		int get_y_cord() const;
		void set_position(const int x, const int y);
		SDL_Point &get_sdl_point();

	private:
		SDL_Point inner;
	};
}

#endif // _POINT_H_
