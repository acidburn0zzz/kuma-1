#ifndef _POINTER_H_
#define _POINTER_H_

#include <SDL.h>
#include <iostream>
#include <string>
#include <tuple>

#include "SDL_events.h"
#include "drawable.h"
#include "posable.h"
#include "rect.h"
#include "texture.h"

class Window;

class Pointer : public Drawable, Posable {
public:
	Pointer(std::string path, Window &window);
	int get_x_pos();
	int get_y_pos();
	std::tuple<int, int> get_pos();
	std::tuple<int, int> set_pos(int x, int y);
	void set_x_pos(int x);
	void set_y_pos(int y);
	void handle_mouse(const SDL_Event &event);
	void draw(Window &window);
	Rect &get_rect();
	Texture &get_texture();
	Texture texture;
	Rect rect;

private:
	int x = 0, y = 0;
};

#endif
