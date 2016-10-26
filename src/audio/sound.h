#ifndef _SOUND_H_
#define _SOUND_H_

#include "exception.h"
#include "sdl_smart_ptr.h"
#include "util.h"

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

// Sound takes any compressed audio format
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
	int channel;
};

class Chunk {
public:
	Chunk() {}
	Chunk(std::string path);
	Mix_Chunk *get_inner();
	int loops;
	Chunk &operator=(const Chunk &copy);
private:
	SharedAudioPtr inner;
};

#endif
