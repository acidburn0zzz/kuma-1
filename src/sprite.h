#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <deque>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <yaml.h>

#include "animation.h"
#include "drawable.h"
#include "posable.h"
#include "rect.h"
#include "sprite_sheet.h"
#include "timer.h"
#include "window.h"

namespace kuma {
	class Animation;
	class Mixer;
	class Timer;
	class Window;

	class Sprite : public AnimatedDrawable, Posable {
	public:
		friend class Entity;
		Sprite() { current = nullptr; };
		void render_front(Window &window, const Timer &timer);
		void from_sheet(const std::string path, Window &window, const int clip_width,
		                const int clip_height, const int margin);
		void from_sheet(const std::string path, Window &window, const int clip_width,
		                const int clip_height);
		void from_yaml(const std::string &path, Window &window);
		void set_animation(const std::string name, const int begin, const int end,
		                   const unsigned rate, const std::string sound_path,
		                   const unsigned sound_rate);
		void play_animation(std::string name);
		void set_current_animation(std::string name);
		void draw(Window &window, const Timer &timer, Mixer &mixer);
		void draw(Window &window, const Timer &timer);
		void draw(Window &window);
		void draw_ex(Window &window, const Timer &timer, Mixer &mixer, double angle);
		Rect &get_rect();
		SpriteSheet sheet;
		std::map<std::string, Animation> animations;
		Animation *current;
		Rect rect;
		Sprite &operator=(const Sprite &copy);

	private:
		unsigned last_time = 0;
		unsigned last_audio_time = 0;
	};
}

#endif // _SPRITE_H_
