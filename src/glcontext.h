#ifndef _GL_CONTEXT_H_
#define _GL_CONTEXT_H_

#include <SDL.h>

#include "window.h"

namespace kuma {
	class Window;
	class GLContext {
	public:
		GLContext(Window &window);
		~GLContext();
		SDL_GLContext &get_sdl_context();

	private:
		SDL_GLContext context;
	};
}

#endif // _GL_CONTEXT_H_
