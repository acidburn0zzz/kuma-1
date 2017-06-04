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

class Mixer;
class Rect;
class Texture;
class Window;

class Animation {
public:
	Animation() {}
	Animation(const std::string name, const unsigned &rate)
	    : name(name), frame_rate(rate){};
	void next_frame();
	void prev_frame();
	void render_front(Window &window, Texture &texture, Rect &dest);
	void render_front(Window &window, Texture &texture, Rect &dest,
			  double angle);
	void set_sound(std::string path, unsigned audio_rate);
	void play_sound(Mixer &mixer);
	std::string &get_name();
	std::deque<Rect> frames;
	unsigned get_frame_rate() const;
	unsigned get_sound_rate() const;
	Animation &operator=(const Animation &copy);
	Chunk sound;

private:
	unsigned sound_rate = 0;
	std::string name;
	unsigned frame_rate;
};

#endif // _ANIMATION_H_
