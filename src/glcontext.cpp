#include "glcontext.h"
using namespace kuma;

GLContext::GLContext(Window &window) { context = SDL_GL_CreateContext(window.window.get()); }

GLContext::~GLContext() { SDL_GL_DeleteContext(context); }

SDL_GLContext &GLContext::get_sdl_context() { return context; }
