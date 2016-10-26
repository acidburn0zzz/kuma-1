#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <SDL.h>
#include <iostream>
#include <map>
#include <tuple>

/// Class to wrap around `SDL_DisplayMode`. Used for accessing information about
/// a display
class DisplayMode {
public:
	DisplayMode(const SDL_DisplayMode mode);
	/// Get's the dimensions of the display
	/// @return Returns a tuple in for of width x height
	std::tuple<int, int> get_dimensions() const;
	/// Gets the width of the display
	int get_width() const;
	/// Gets the height of the dispaly
	int get_height() const;
	/// Gets the refresh rate of the dispaly
	int get_refresh_rate() const;
	/// Gets the center X coordinate of the display
	int get_center_x_cord(const int width) const;
	/// Gets the center Y coordinate of the display
	int get_center_y_cord(const int height) const;
	SDL_DisplayMode *get_sdl_mode();
	SDL_DisplayMode inner_mode;

private:
	int display_width;
	int display_height;
	int display_refresh_rate;
};

class Displays {
public:
	Displays();
	void populate_display_data();
	std::map<int, DisplayMode> displays;
};

#endif // _DISPLAY_H_
