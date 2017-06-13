#include "display.h"

using namespace kuma;

DisplayMode::DisplayMode(const SDL_DisplayMode mode) { inner_mode = mode; }

std::tuple<int, int> DisplayMode::get_dimensions() const {
	return std::make_tuple(inner_mode.w, inner_mode.h);
}

int DisplayMode::get_refresh_rate() const { return inner_mode.refresh_rate; }

int DisplayMode::get_width() const { return inner_mode.w; }

int DisplayMode::get_height() const { return inner_mode.h; }

int DisplayMode::get_center_x_cord(const int width) const {
	return ((inner_mode.w * 0.5) - (width * 0.5));
}

int DisplayMode::get_center_y_cord(const int height) const {
	return ((inner_mode.h * 0.5) - (height * 0.5));
}

SDL_DisplayMode *DisplayMode::get_sdl_mode() { return &inner_mode; }

Displays::Displays() { populate_display_data(); }

void Displays::populate_display_data() {
	for (int i = 0; i < SDL_GetNumVideoDisplays(); i++) {
		SDL_DisplayMode mode;
		SDL_GetDisplayMode(i, 0, &mode);
		displays.insert(
		    std::pair<int, DisplayMode>(i, DisplayMode(mode)));
	}
}
