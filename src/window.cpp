#include "window.h"

Window::Window() {}

Window::Window(std::string title, int x, int y, int w, int h) {
	window = set_window(title, x, y, w, h, WindowFlag::Shown);
	renderer = set_renderer(RenderFlag::Accelerated);
	SDL_RenderSetLogicalSize(renderer.get(), w, h);
}

Window::Window(std::string title, int x, int y, int w, int h, WindowFlag flag) {
	window = set_window(title, x, y, w, h, flag);
	renderer = set_renderer(RenderFlag::Accelerated);
	SDL_RenderSetLogicalSize(renderer.get(), w, h);
}

Window::Window(std::string title, int x, int y, int w, int h,
	       WindowFlag win_flag, RenderFlag ren_flag) {
	window = set_window(title, x, y, w, h, win_flag);
	renderer = set_renderer(ren_flag);
	SDL_RenderSetLogicalSize(renderer.get(), w, h);
}

SDL_Renderer *Window::get_renderer() { return this->renderer.get(); }

void Window::poll_dim_change() { SDL_GetWindowSize(window.get(), &w, &h); }

std::tuple<int, int> Window::get_dimensions() {
	SDL_GetWindowSize(window.get(), &w, &h);
	return std::make_tuple(w, h);
}

int Window::get_height() {
	SDL_GetWindowSize(window.get(), &w, &h);
	return h;
}

int Window::get_width() {
	SDL_GetWindowSize(window.get(), &w, &h);
	return w;
}

void Window::set_renderer_scaling(int w, int h) {
	SDL_RenderSetLogicalSize(renderer.get(), w, h);
}

void Window::render_clear() { SDL_RenderClear(this->renderer.get()); }

void Window::render_present() { SDL_RenderPresent(this->renderer.get()); }

SharedRenderPtr Window::set_renderer(RenderFlag ren_flag) {
	return SharedRenderPtr(SDL_CreateRenderer(
	    window.get(), -1, static_cast<uint32_t>(ren_flag)));
}

SharedWindowPtr Window::set_window(std::string title, int x, int y, int w,
				   int h, WindowFlag win_flag) {
	this->w = w;
	this->h = h;
	return SharedWindowPtr(SDL_CreateWindow(
	    title.c_str(), x, y, w, h, static_cast<uint32_t>(win_flag)));
}

void Window::render_frame() {
	render_present();
	render_clear();
	++frame_count;
}

void Window::inc_frame_count() { frame_count++; }

uint32_t Window::get_frame_count() { return frame_count; }

void Window::write_variables(ScriptContext &context) {
	context.new_usertype<Window>("window",
			"get_width", &Window::get_width,
			"get_height", &Window::get_height
			);
}

Window &Window::operator=(const Window &copy) {
	w = copy.w;
	h = copy.h;
	frame_count = copy.frame_count;
	window = copy.window;
	renderer = copy.renderer;
	return *this;
}

Window::Window(const Window &copy) {
	w = copy.w;
	h = copy.h;
	frame_count = copy.frame_count;
	window = copy.window;
	renderer = copy.renderer;
}

void Window::set_icon(std::string path) {
	SurfacePtr image = SurfacePtr(IMG_Load(path.c_str()), SDL_Delete());
	SDL_SetWindowIcon(window.get(), image.get());
	image.reset();
}
