#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <deque>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "audio/mixer.h"
#include "audio/sound.h"
#include "rect.h"
#include "texture.h"
#include "window.h"
#include "flip.h"
#include "point.h"

class Animation {
public:
	Animation() {}
	Animation(const std::string name, const unsigned &rate)
	    : name(name), rate(rate){};
	std::string name;
	void next_frame();
	void prev_frame();
	void render_front(Window &window, Texture &texture, Rect &dest);
	void render_front(Window &window, Texture &texture, Rect &dest, double angle);
	void set_sound(std::string path, unsigned audio_rate);
	void play_sound(Mixer &mixer);
	std::deque<Rect> frames;
	unsigned rate;
	Animation &operator=(const Animation &copy);
	Chunk sound;
	unsigned sound_rate = 0;
};

#endif // _ANIMATION_H_
