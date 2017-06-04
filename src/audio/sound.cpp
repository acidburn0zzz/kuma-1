#include "sound.h"

#include "SDL_mixer.h"

Music::Music() {}

Music::Music(std::string path) {
	if (!file_exists(path)) {
		throw KException("Music (): File '" + path + "' not found");
	}
	inner = SharedMusicPtr(Mix_LoadMUS(path.c_str()));
	if (!inner) {
		throw KException(
		    "Music (): Music not allocated correctly for path '" +
		    path + "'");
	}
	loops = 0;
}

Music &Music::operator=(const Music &copy) {
	loops = copy.loops;
	channel = copy.channel;
	inner = copy.inner;
	return *this;
}

Mix_Music *Music::get_inner() { return this->inner.get(); }

Chunk::Chunk(std::string path) {
	if (!file_exists(path)) {
		throw KException("Chunk (): File '" + path + "' not found");
	}
	inner = SharedAudioPtr(Mix_LoadWAV(path.c_str()));
	loops = 0;
}

Mix_Chunk *Chunk::get_inner() { return inner.get(); }

Chunk &Chunk::operator=(const Chunk &copy) {
	loops = copy.loops;
	inner = copy.inner;
	return *this;
}
