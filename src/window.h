#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <memory>
#include "rect.h"
#include "script_context.h"
#include "sdl_smart_ptr.h"
#include "texture.h"
#include "point.h"
#include "flip.h"

class Texture;

enum class WindowFlag {
	Fullscreen = SDL_WINDOW_FULLSCREEN,
	FullscreenDestkop = SDL_WINDOW_FULLSCREEN_DESKTOP,
	OpenGl = SDL_WINDOW_OPENGL,
	Shown = SDL_WINDOW_SHOWN,
	Hidden = SDL_WINDOW_HIDDEN,
	Borderless = SDL_WINDOW_BORDERLESS,
	Resizable = SDL_WINDOW_RESIZABLE,
	Minimized = SDL_WINDOW_MINIMIZED,
	Maximized = SDL_WINDOW_MAXIMIZED,
	InputGrabbed = SDL_WINDOW_INPUT_GRABBED,
	InputFocus = SDL_WINDOW_INPUT_FOCUS,
	MouseFocus = SDL_WINDOW_MOUSE_FOCUS,
	Foreign = SDL_WINDOW_FOREIGN,
	AllowHighDpi = SDL_WINDOW_ALLOW_HIGHDPI,
};

enum class RenderFlag {
	Software = SDL_RENDERER_SOFTWARE,
	Accelerated = SDL_RENDERER_ACCELERATED,
	PresentVSync = SDL_RENDERER_PRESENTVSYNC,
	TargetTexture = SDL_RENDERER_TARGETTEXTURE,
};

class Window {
public:
	/// Default constructor. Not entended for use.
	Window();
	/// Constructor meant for general use. Where the other constructors
	/// offer options as far as initialization flags, this option does not.
	/// Defaults `WindowFlag` to `Shown`, and `RenderFlag` to `Accelerated`
	Window(std::string title, int x, int y, int w, int h);
	Window(std::string title, int x, int y, int w, int h, WindowFlag flag);
	Window(std::string title, int x, int y, int w, int h,
	       WindowFlag win_flag, RenderFlag ren_flag);
	template <typename T> void render_texture(T &t, Rect &rect);
	template <typename T> void render(T &t, Rect &rect);
	template <typename T> void render_src_dst(T &t, Rect &src, Rect &dest);
	void render(Texture &texture, int x, int y, SDL_Point &point);
	void render(Texture &texture, Rect &dest, SDL_Point &point);
	void render(Texture &texture, Rect &src, Rect &dest);
	void render_ex(Texture &texture, Rect &src, Rect &dest, double angle);
	void render_clear();
	void render_present();
	void render_frame();
	void set_icon(std::string path);
	void set_renderer_scaling(int w, int h);
	void poll_dim_change();
	void write_variables(ScriptContext &context);
	std::tuple<int, int> get_dimensions();
	SDL_Renderer *get_renderer();
	int get_height();
	int get_width();
	uint32_t get_frame_count();
	Window(const Window &copy);
	Window &operator=(const Window &copy);
	SharedWindowPtr set_window(std::string title, int x, int y, int w,
				   int h, WindowFlag win_flag);
	SharedRenderPtr set_renderer(RenderFlag ren_flag);

private:
	void inc_frame_count();
	int w, h;
	unsigned frame_count;
	SharedWindowPtr window;
	SharedRenderPtr renderer;
};

template <typename T> void Window::render_texture(T &t, Rect &rect) {
	SDL_RenderCopy(renderer.get(), t.get_sdl_texture(), nullptr,
		       rect.get_sdl_rect());
}

template <typename T> void Window::render(T &t, Rect &rect) {
	SDL_RenderCopy(renderer.get(), t.texture.get_sdl_texture(), nullptr,
		       rect.get_sdl_rect());
}

template <typename T> void Window::render_src_dst(T &t, Rect &src, Rect &dest) {
	SDL_RenderCopy(renderer.get(), t.texture.get_sdl_texture(),
		       src.get_sdl_rect(), dest.get_sdl_rect());
}

#endif
