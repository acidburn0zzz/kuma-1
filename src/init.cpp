#include "init.h"

Init::Init() {
	set_init_flag = InitFlag::InitEverything;
	set_img_init_flag = ImgInitFlag::InitAll;
	set_mix_init_flag = MixInitFlag::InitFlac | MixInitFlag::InitOgg;
	init_sdl(set_init_flag);
	init_sdl_image(set_img_init_flag);
	init_sdl_ttf();
	init_sdl_mixer(set_mix_init_flag);
}

Init::Init(InitFlag sys_flag, ImgInitFlag img_flag) {
	set_init_flag = sys_flag;
	set_img_init_flag = img_flag;
	init_sdl(sys_flag);
	init_sdl_image(img_flag);
	init_sdl_ttf();
}

Init::~Init() {
	quit_sdl();
	quit_sdl_image();
	quit_sdl_ttf();
	quit_sdl_mixer();
}

void Init::init_sdl(InitFlag flag) {
	if (SDL_Init(static_cast<uint32_t>(flag)) != 0) {
		std::string sdl_error = SDL_GetError();
		throw KException("SDL could not be init: " + sdl_error);
	}
}

void Init::init_sdl_image(ImgInitFlag flag) {
	uint32_t init = IMG_Init(static_cast<uint32_t>(flag));
	if (init != static_cast<uint32_t>(flag)) {
		std::string sdl_error = IMG_GetError();
		throw KException("SDL_img could not be init: " + sdl_error);
	}
}

void Init::init_sdl_ttf() {
	if (TTF_Init() != 0) {
		std::string sdl_error = TTF_GetError();
		throw KException("SDL_ttf could not be init: " + sdl_error);
	}
}

void Init::init_sdl_mixer(MixInitFlag mix_flag) {
	uint32_t init = Mix_Init(static_cast<uint32_t>(mix_flag));
	if (init != static_cast<uint32_t>(mix_flag)) {
		std::string sdl_error = Mix_GetError();
		throw KException("SDL_mixer could not be init: " + sdl_error);
	}
}

void Init::quit_sdl() { SDL_Quit(); }

void Init::quit_sdl_image() { IMG_Quit(); }

void Init::quit_sdl_ttf() { TTF_Quit(); }

void Init::quit_sdl_mixer() {
	while (Mix_Init(0))
		Mix_Quit();
}
