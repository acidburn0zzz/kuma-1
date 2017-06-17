#include "texture.h"

#include "rw.h"
#include "util.h"

using namespace kuma;

Texture::Texture() {}

Texture::Texture(std::string path, Window &window) {
	image_path = path;
	from_image(path, window);
	SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h);
}

Texture::Texture(RW &rw, Window &window) { from_rw(rw, window); }

void Texture::from_rw(RW &rw, Window &window) {
	if (!rw.get()) {
		throw KException("Texture (): SDL_RWops pointer to nullptr");
	}
	texture = SharedTexturePtr(IMG_LoadTexture_RW(window.get_renderer(), rw.get(), 0));
	SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h);
	image_path = "FROM_RW";
}

Texture::~Texture() { free(); }

void Texture::set_dimensions(const std::tuple<int, int> dim) {
	w = std::get<0>(dim);
	h = std::get<1>(dim);
}

void Texture::set_dimensions(const int w, const int h) {
	this->w = w;
	this->h = h;
}

void Texture::from_surface(const SharedSurfacePtr surface, Window &window) {
	texture =
	    SharedTexturePtr(SDL_CreateTextureFromSurface(window.get_renderer(), surface.get()));
}

void Texture::from_image(std::string path, Window &window) {
	if (!file_exists(path)) {
		throw KException("Texture (from_image): File '" + path + "' does not exist");
	}
	image_path = path;
	texture = SharedTexturePtr(IMG_LoadTexture(window.get_renderer(), path.c_str()));
	SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h);
}

std::string Texture::get_image_path() { return image_path; }

void Texture::set_image_path(std::string path) { image_path = path; }

int Texture::get_width() { return w; }

int Texture::get_height() { return h; }

void Texture::set_height(const int h) { this->h = h; }

void Texture::set_width(const int w) { this->w = w; }

std::tuple<int, int> Texture::get_dimensions() { return std::make_tuple(w, h); }

SDL_Texture *Texture::get_sdl_texture() { return texture.get(); }

Texture &Texture::get_texture() { return *this; }

void Texture::free() {
	if (texture.get() != nullptr) {
		texture.reset();
	}
}

Texture &Texture::operator=(const Texture &copy) {
	if (&copy == this) {
		return *this;
	}
	image_path = copy.image_path;
	w = copy.w;
	h = copy.h;
	texture = copy.texture;
	orientation = copy.orientation;
	return *this;
}

Texture Texture::swap(Texture &swap) {
	std::swap(w, swap.w);
	std::swap(h, swap.h);
	std::swap(texture, swap.texture);
	std::swap(orientation, swap.orientation);
	return *this;
}

Texture::Texture(const Texture &copy) {
	image_path = copy.image_path;
	w = copy.w;
	h = copy.h;
	texture = copy.texture;
	orientation = copy.orientation;
}
