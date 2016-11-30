#include "tile.h"

Tile::Tile(std::string path, Window &window, int x, int y) {
	texture.from_image(path, window);
	rect.set_dimensions(
	    std::make_tuple(texture.get_width(), texture.get_height()));
	rect.set_position(x, y);
	rect.set_outline_color(0, 0, 255, 255);
}

Tile::Tile(Texture &texture, int x, int y) {
	this->texture = texture;
	rect.set_dimensions(texture.get_width(), texture.get_height());
	rect.set_position(x, y);
	rect.set_outline_color(0, 0, 255, 255);
}

void Tile::draw(Window &window) {
	SDL_RenderCopy(window.get_renderer(), texture.get_sdl_texture(),
			nullptr, rect.get_sdl_rect());
}
