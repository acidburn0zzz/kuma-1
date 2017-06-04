#ifndef _MIXER_H_
#define _MIXER_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

#include "SDL_audio.h"
#include "exception.h"
#include "sdl_smart_ptr.h"
#include "sound.h"
#include "util.h"

class Chunk;
class Music;

enum class AudioMode {
	Mono = 1,
	Stereo = 2,
};

enum class AudioFormat {
	U8 = AUDIO_U8,
	S8 = AUDIO_S8,
	U16 = AUDIO_U16SYS,
	S16 = AUDIO_S16SYS,
};

class Mixer {
public:
	Mixer();
	Mixer(int freq, AudioFormat format, AudioMode mode, int sample_size);
	void play(Music &music);
	void play(Chunk &chunk);
	void play(Music &music, int loops);
	void set_master_volume(int volume);
	void dec_master_volume(int step);
	void inc_master_volume(int step);
	void set_volume(int vol);
	void set_mix_channels(int channels);
	void pause_music();
	void resume_music();
	int get_volume();
	bool music_paused();

private:
	int volume = 0;
	void get_spec();
	int frequency = 0;
	AudioFormat format = AudioFormat::U8;
	AudioMode mode = AudioMode::Stereo;
	int mix_channels = 0;
	int sample_size = 0;
};

#endif
