#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <tuple>

#include "SDL_render.h"
#include "exception.h"
#include "flip.h"
#include "rw.h"
#include "sdl_smart_ptr.h"
#include "util.h"
#include "window.h"

class RW;
class Window;

class Texture {
public:
	Texture();
	Texture(std::string path, Window &window);
	Texture(RW &rw, Window &window);
	~Texture();
	int get_width();
	int get_height();
	void from_image(std::string path, Window &window);
	void from_rw(RW &rw, Window &window);
	void orientation_reset();
	void set_width(const int width);
	void set_height(const int height);
	std::tuple<int, int> get_dimensions();
	void set_dimensions(const std::tuple<int, int> dim);
	void set_dimensions(const int w, const int h);
	SDL_Texture *get_sdl_texture();
	void set_image_path(std::string);
	std::string get_image_path();
	void free();
	void from_surface(const SharedSurfacePtr surface, Window &window);
	Texture &get_texture();
	Texture(const Texture &copy);
	Texture &operator=(const Texture &copy);
	Texture swap(Texture &swap);

private:
	std::string image_path;
	int w, h;
	SharedTexturePtr texture;
	Flip orientation = Flip::None;
};

#endif
