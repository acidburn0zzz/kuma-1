#ifndef _SOUND_H_
#define _SOUND_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdint.h>
#include <string>

#include "exception.h"
#include "sdl_smart_ptr.h"
#include "util.h"

// Sound takes any compressed audio format
namespace kuma {
	class Music {
	public:
		Music();
		Music(std::string path);
		Mix_Music *get_inner();
		void set_position(int chan, uint16_t angle, uint8_t dist);
		int loops;
		Music &operator=(const Music &copy);

	private:
		SharedMusicPtr inner;
		int channel = 0;
	};

	class Chunk {
	public:
		Chunk() {}
		Chunk(std::string path);
		Mix_Chunk *get_inner();
		int loops = 0;
		Chunk &operator=(const Chunk &copy);

	private:
		SharedAudioPtr inner;
	};
}

#endif
