#include "text.h"

#include "util.h"

using namespace kuma;
class Timer;
class Window;

Text::Text() {}

Text::Text(const std::string &path, const int size) { open_font(path, size); }

Text::Text(const std::string &path, const int size, Window &window,
	   int col_width, int x, int y) {
	if (inner_text.empty()) {
		inner_text = "(EMPTY)";
	}
	set_color(255, 255, 255, 0);
	open_font(path, size);
	column_width = col_width;
	generate_texture(window);
	rect.set_position(x, y);
	temp_surface.reset();
}

Rect &Text::get_rect() { return rect; }

std::string Text::get_text() const { return inner_text; }

void Text::set_text(const std::string &text, Window &window) {
	if (inner_text == text) {
		return;
	} else {
		inner_text = text;
		generate_texture(window);
	}
}

void Text::generate_texture(Window &window) {
	temp_surface = SharedSurfacePtr(TTF_RenderText_Blended_Wrapped(
	    font.get(), inner_text.c_str(), font_color, column_width));
	texture.from_surface(temp_surface, window);
	texture.set_dimensions(temp_surface.get()->w, temp_surface.get()->h);
	rect.set_dimensions(texture.get_dimensions());
	temp_surface.reset();
}

void Text::set_position(int x, int y) { rect.set_position(x, y); }

void Text::open_font(const std::string &path, const int size) {
	if (!file_exists(path)) {
		throw KException("Font '" + path + "' doesn't exist!");
	}
	texture.set_image_path(path);
	font = SharedTextPtr(TTF_OpenFont(path.c_str(), size));
	TTF_SetFontKerning(font.get(), 1);
}

void Text::set_color(const uint8_t R, const uint8_t G, const uint8_t B,
		     const uint8_t A) {
	font_color.r = R;
	font_color.g = G;
	font_color.b = B;
	font_color.a = A;
}

void Text::set_text_from_int(int num) { inner_text = std::to_string(num); }

void Text::set_text_from_float(float num) { inner_text = std::to_string(num); }

void Text::set(Window &window, int col_width) {
	column_width = col_width;
	generate_texture(window);
}

void Text::draw(Window &window, const Timer &) {
	generate_texture(window);
	SDL_RenderCopy(window.get_renderer(), texture.get_sdl_texture(),
		       nullptr, rect.get_sdl_rect());
}
