#include "sprite.h"

void Sprite::from_sheet(const std::string path, Window &window, int clip_width,
			int clip_height, int margin) {
	sheet = SpriteSheet(path, window, clip_width, clip_height, margin);
	rect.set_dimensions(clip_width, clip_height);
}

void Sprite::from_yaml(const std::string &path, Window &window) {
	YAML::Node from = YAML::LoadFile(path);
	if (from["from_sheet"]) {
		if (from["clip_width"] && from["clip_height"]) {
			if (from["margin"]) {
				from_sheet(from["from_sheet"].as<std::string>(),
					   window, from["clip_width"].as<int>(),
					   from["clip_height"].as<int>(),
					   from["margin"].as<int>());
			} else {
				from_sheet(from["from_sheet"].as<std::string>(),
					   window, from["clip_width"].as<int>(),
					   from["clip_height"].as<int>(), 0);
			}
		}
	}
	if (from["animations"]) {
		std::for_each(
		    from["animations"].begin(), from["animations"].end(),
		    [this](YAML::Node animation) {
			    set_animation(
				animation["name"].as<std::string>(),
				// Range for animations is start, end, rate
				animation["range"][0].as<int>(),
				animation["range"][1].as<int>(),
				animation["range"][2].as<int>(),
				animation["sound"].as<std::string>(),
				animation["sound-rate"].as<int>());
		    });
	}
}

void Sprite::set_animation(const std::string name, const int begin,
			   const int end, const unsigned rate,
			   const std::string sound_path,
			   const unsigned sound_rate) {
	if (end > (int)sheet.cells.size()) {
		throw KException("Sprite::set_animation(): tried to assign "
				 "frames > sheet size");
	}
	animations.insert(
	    std::pair<std::string, Animation>(name, Animation(name, rate)));
	if (!sound_path.empty()) {
		animations[name].set_sound(sound_path, sound_rate);
	}
	// Range for animations start at 1 and not 0
	for (int i = begin - 1; i <= end; i++) {
		animations[name].frames.push_back(sheet.cells[i]);
	}
}

void Sprite::draw(Window &window, const Timer &timer) {
	if (timer.get_ticks() > (last_time + current.rate)) {
		current.next_frame();
		last_time = timer.get_ticks();
	}
	current.render_front(window, sheet.texture, rect);
}

void Sprite::draw(Window &window, const Timer &timer, Mixer &mixer) {
	if (timer.get_ticks() > (last_time + current.rate)) {
		current.next_frame();
		last_time = timer.get_ticks();
	}
	if (timer.get_ticks() > (last_audio_time + current.sound_rate)) {
		current.play_sound(mixer);
		last_audio_time = timer.get_ticks();
	}
	current.render_front(window, sheet.texture, rect);
}

void Sprite::draw(Window &window) {
	current.render_front(window, sheet.texture, rect);
}

void Sprite::draw_ex(Window &window, const Timer &timer, Mixer &mixer, double angle) {
	current.render_front(window, sheet.texture, rect, angle);
}

Rect &Sprite::get_rect() { return rect; }

void Sprite::set_current_animation(std::string name) {
	if (current.name != name) {
		current = animations[name];
	}
}


void Sprite::play_animation(std::string name) {
	if (current.name != name) {
		current = animations[name];
	}
}

Sprite &Sprite::operator=(const Sprite &copy) {
	last_time = copy.last_time;
	last_audio_time = copy.last_audio_time;
	sheet = copy.sheet;
	animations = copy.animations;
	rect = copy.rect;
	return *this;
}
