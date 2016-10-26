#include "animation.h"

void Animation::next_frame() {
	frames.push_back(frames.front());
	frames.pop_front();
}

void Animation::prev_frame() {
	frames.push_front(frames.back());
	frames.pop_back();
}

void Animation::render_front(Window &window, Texture &texture, Rect &dest) {
	window.render(texture, frames.front(), dest);
}


void Animation::render_front(Window &window, Texture &texture, Rect &dest, double angle) {
	window.render_ex(texture, frames.front(), dest, angle);
}

void Animation::set_sound(std::string path, unsigned audio_rate) {
	sound = Chunk(path);
	sound_rate = audio_rate;
}

void Animation::play_sound(Mixer &mixer) { mixer.play(sound); }

Animation &Animation::operator=(const Animation &copy) {
	frames = copy.frames;
	sound = copy.sound;
	rate = copy.rate;
	sound_rate = copy.sound_rate;
	return *this;
}
