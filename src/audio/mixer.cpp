#include "mixer.h"

Mixer::Mixer()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
		std::string sdl_error = Mix_GetError();
		throw KException("Mixer (): " + sdl_error);
	}
	mode = AudioMode::Stereo,
	frequency = 44100;
	format = AudioFormat::U16;
	sample_size = 2048;
	volume = MIX_MAX_VOLUME;
}

Mixer::Mixer(int freq, AudioFormat format, AudioMode mode, int sample_size)
{
	if (Mix_OpenAudio(freq, static_cast<uint16_t>(format), static_cast<int>(mode), sample_size) != 0) {
		std::string sdl_error = Mix_GetError();
		throw KException("Mixer (): " + sdl_error);
	}
	volume = MIX_MAX_VOLUME;
}

void Mixer::get_spec()
{
	//Mix_QuerySpec(&frequency, static_cast<uint16_t>(format), static_cast<int>(mode));
}

void Mixer::play(Music &music)
{
	Mix_PlayMusic(music.get_inner(), music.loops);
}

void Mixer::play(Music &music, int loop_times)
{
	Mix_PlayMusic(music.get_inner(), loop_times);
}

void Mixer::play(Chunk &chunk)
{
	Mix_PlayChannel(-1, chunk.get_inner(), chunk.loops);
}

void Mixer::set_master_volume(int volume)
{
	Mix_Volume(-1, volume);
	Mix_VolumeMusic(volume);
}

void Mixer::dec_master_volume(int step)
{
	if (volume >= 0) {
		volume -= step;
	}
	set_master_volume(volume);
	std::cout << "MASTER VOL: " << Mix_VolumeMusic(-1) << '\n';
}

void Mixer::inc_master_volume(int step)
{
	if (volume <= 128) {
		volume += step;
	}
	set_master_volume(volume);
	std::cout << "MASTER VOL: " << Mix_VolumeMusic(-1) << '\n';
}

int Mixer::get_volume() { return volume; }

void Mixer::set_mix_channels(int channels)
{
	Mix_AllocateChannels(channels);
}

void Mixer::pause_music()
{
	Mix_PauseMusic();
}

void Mixer::resume_music()
{
	Mix_ResumeMusic();
}

bool Mixer::music_paused()
{
	return Mix_PausedMusic();
}

