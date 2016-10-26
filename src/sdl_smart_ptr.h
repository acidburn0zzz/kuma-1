#ifndef _SDL_SMART_PTR_H_
#define _SDL_SMART_PTR_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <memory>

struct SDL_Delete {
	void operator()(SDL_Surface *ptr) {
		if (ptr)
			SDL_FreeSurface(ptr);
	}
	void operator()(SDL_Texture *ptr) {
		if (ptr)
			SDL_DestroyTexture(ptr);
	}
	void operator()(SDL_Renderer *ptr) {
		if (ptr)
			SDL_DestroyRenderer(ptr);
	}
	void operator()(SDL_Window *ptr) {
		if (ptr)
			SDL_DestroyWindow(ptr);
	}
	void operator()(TTF_Font *ptr) {
		if (ptr)
			TTF_CloseFont(ptr);
	}
	void operator()(Mix_Chunk *ptr) {
		if (ptr)
			Mix_FreeChunk(ptr);
	}
	void operator()(Mix_Music *ptr) {
		if (ptr)
			Mix_FreeMusic(ptr);
	}
	void operator()(SDL_RWops *ptr) {
		if (ptr)
			SDL_FreeRW(ptr);
	}
};

typedef std::unique_ptr<SDL_Surface, SDL_Delete> SurfacePtr;
typedef std::unique_ptr<SDL_Window, SDL_Delete> WindowPtr;
typedef std::unique_ptr<SDL_Texture, SDL_Delete> TexturePtr;
typedef std::unique_ptr<SDL_Renderer, SDL_Delete> RenderPtr;
typedef std::unique_ptr<TTF_Font, SDL_Delete> TextPtr;
typedef std::unique_ptr<Mix_Chunk, SDL_Delete> AudioPtr;
typedef std::unique_ptr<Mix_Music, SDL_Delete> MusicPtr;
typedef std::unique_ptr<SDL_RWops, SDL_Delete> RWPtr;

template <class T, class D = std::default_delete<T>>
struct sdl_shared_ptr : public std::shared_ptr<T> {
	explicit sdl_shared_ptr(T *t = nullptr) : std::shared_ptr<T>(t, D()) {}
	void reset(T *t = nullptr) { std::shared_ptr<T>::reset(t, D()); }
};

typedef sdl_shared_ptr<SDL_Surface, SDL_Delete> SharedSurfacePtr;
typedef sdl_shared_ptr<SDL_Texture, SDL_Delete> SharedTexturePtr;
typedef sdl_shared_ptr<SDL_Renderer, SDL_Delete> SharedRenderPtr;
typedef sdl_shared_ptr<SDL_Window, SDL_Delete> SharedWindowPtr;
typedef sdl_shared_ptr<TTF_Font, SDL_Delete> SharedTextPtr;
typedef sdl_shared_ptr<Mix_Chunk, SDL_Delete> SharedAudioPtr;
typedef sdl_shared_ptr<Mix_Music, SDL_Delete> SharedMusicPtr;
typedef sdl_shared_ptr<SDL_RWops, SDL_Delete> SharedRWPtr;

#endif
