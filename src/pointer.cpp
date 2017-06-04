#include "pointer.h"

#include "SDL_mouse.h"

class Window;

Pointer::Pointer(std::string path, Window &window) {
	texture.from_image(path, window);
	SDL_ShowCursor(SDL_DISABLE);
	rect.set_dimensions(
	    std::make_tuple(texture.get_width(), texture.get_height()));
}

Rect &Pointer::get_rect() { return rect; }

Texture &Pointer::get_texture() { return texture; }

void Pointer::handle_mouse(const SDL_Event &event) {
	if (event.type == SDL_MOUSEMOTION) {
		if ((event.motion.x != rect.get_x_cord()) ||
		    event.motion.y != rect.get_y_cord()) {
			rect.set_position(
			    std::make_tuple(event.motion.x, event.motion.y));
		}
	}
}

void Pointer::draw(Window &window) {
	SDL_RenderCopy(window.get_renderer(), texture.get_sdl_texture(),
		       nullptr, rect.get_sdl_rect());
}
