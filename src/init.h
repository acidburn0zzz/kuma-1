#ifndef _INIT_H_
#define _INIT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdint.h>

#include "exception.h"

namespace kuma {
	enum class MixInitFlag {
		InitFlac = MIX_INIT_FLAC,
		InitMod = MIX_INIT_MOD,
		InitMp3 = MIX_INIT_MP3,
		InitOgg = MIX_INIT_OGG,
		InitAll =
		    MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG,
	};

	inline MixInitFlag operator|(MixInitFlag a, MixInitFlag b) {
		return static_cast<MixInitFlag>(static_cast<uint32_t>(a) |
						static_cast<uint32_t>(b));
	}

	/// Flags for initializing SDL subsystems
	enum class InitFlag {
		/// Initializes SDL's timer subsystem
		InitTimer = SDL_INIT_TIMER,
		/// Initializes SDL's audio subsystem
		InitAudio = SDL_INIT_AUDIO,
		/// Initializes SDL's video subsystem
		InitVideo = SDL_INIT_VIDEO,
		/// Initializes SDL's joystick subsystem
		InitJoystick = SDL_INIT_JOYSTICK,
		/// Initializes SDL's haptic feedback subsystem
		InitHaptic = SDL_INIT_HAPTIC,
		/// Initializes SDL's game controller subsystem
		InitGameController = SDL_INIT_GAMECONTROLLER,
		/// Initializes SDL's event subsystem
		InitEvents = SDL_INIT_EVENTS,
		/// Initializes all of SDL's subsystems
		InitEverything = SDL_INIT_EVERYTHING,
	};

	inline InitFlag operator|(InitFlag a, InitFlag b) {
		return static_cast<InitFlag>(static_cast<uint32_t>(a) |
					     static_cast<uint32_t>(b));
	}

	/// Flags for initializing SDL_img image support
	enum class ImgInitFlag {
		/// Initializes SDL_img PNG support
		InitPng = IMG_INIT_PNG,
		/// Initializes SDL_img JPG support
		InitJpg = IMG_INIT_JPG,
		/// Initializes SDL_img TIF support
		InitTif = IMG_INIT_TIF,
		/// Initializes support for PNG, JPG, and TIF in SDL_img
		InitAll = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF,
	};

	inline ImgInitFlag operator|(ImgInitFlag a, ImgInitFlag b) {
		return static_cast<ImgInitFlag>(static_cast<uint32_t>(a) |
						static_cast<uint32_t>(b));
	}

	/// Initializes SDL, SDL_img and SDL_ttf subsystems for use within
	/// `kuma`
	///
	/// This class initializes all SDL systems for use. This class must be
	/// instantiated in order to use kuma
	class Init {
	public:
		/// The default constructor for `Init` initializes all of SDL's
		/// subsystems and loads support for all image formats supported
		/// by
		/// SDL_img
		Init();
		/// Alternate constructor
		/// @param sys_flag SDL subsystem initialization flag
		/// @param img_flag SDL_img image support initialization flag
		///
		/// Allows for initialization of specific subsystems and
		/// specific
		/// support of image formats for SDL_img
		Init(InitFlag sys_flag, ImgInitFlag img_flag);
		/// The default destructor terminates all SDL, SDL_img, and
		/// SDL_ttf
		/// instances cleanly, freeing all used memory
		~Init();
		InitFlag set_init_flag;
		ImgInitFlag set_img_init_flag;
		MixInitFlag set_mix_init_flag;
		Init &operator=(const Init copy);

	private:
		void init_sdl(InitFlag flag);
		void init_sdl_image(ImgInitFlag img_flag);
		void init_sdl_ttf();
		void init_sdl_mixer(MixInitFlag mix_flag);
		void quit_sdl();
		void quit_sdl_image();
		void quit_sdl_ttf();
		void quit_sdl_mixer();
	};
}

#endif
