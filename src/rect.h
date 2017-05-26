#ifndef _RECT_H_
#define _RECT_H_

#include <SDL.h>
#include <iostream>
#include <tuple>
#include "drawable.h"

class Window;

/// Class used to represent a rectangle on a 2D surface. This is used for
/// setting all coordinates in `kuma` as well as sprite width and height.
/// All positions are set and gotten in (X, Y).
class Rect : public Drawable {
public:
	friend class Entity;
	friend class Player;
	/// Default constructor, set's `x`, `y`, `w`, and `h` to `0`
	Rect();
	/// Instantiates a rectangle with `x` and `y` values to `0`
	/// @param w Width of rectangle
	/// @param h Height of rectangle
	Rect(int w, int h);
	/// Instantiates a rectangle with the given parameters.
	/// @param x X position of the rectangle
	/// @param y Y position of the rectangle
	/// @param w Width of rectangle
	/// @param h Height of rectangle
	Rect(int x, int y, int w, int h);
	SDL_Rect *get_sdl_rect();
	/// Set the position of the rectangle
	/// @param x Sets X position
	/// @param y Sets Y position
	void set_position(const int x, const int y);
	/// Set the position of the rectangle
	/// @param pos A tuple, in the form of X position and Y position
	void set_position(const std::tuple<int, int> pos);
	/// Get's the position of the rectangle
	/// @return Returns a tuple of the rectangles position in the form of
	/// X position and Y position
	std::tuple<int, int> get_position() const;
	/// Set's X position only
	void set_x_cord(const int x);
	/// Set's Y position only
	void set_y_cord(const int y);
	void set_outline_color(const uint8_t R, const uint8_t G,
			       const uint8_t B, const uint8_t A);
	void draw(Window &window);
	int get_x_cord();
	int get_y_cord();
	int get_width();
	int get_height();
	void set_width(const int w);
	void set_height(const int h);
	std::tuple<int, int> get_dimensions();
	void set_dimensions(const std::tuple<int, int> dim);
	void set_dimensions(const int w, const int h);
	/// Set's the rectangles position to (0, 0)
	void reset_position();
	void set_velocities(const int x, const int y);
	void set_x_velocity(const int x);
	void set_y_velocity(const int y);
	int get_x_velocity() const;
	int get_y_velocity() const;
	Rect &operator=(const Rect &copy);

private:
	int x_velocity = 0;
	int y_velocity = 0;
	SDL_Rect rect;
	SDL_Color rect_color;
	int x = 0, y = 0, w = 0, h = 0;
};

#endif
