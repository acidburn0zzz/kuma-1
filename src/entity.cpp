#include "entity.h"

#include <fstream>
#include <stdint.h>

#include "node/impl.h"
#include "node/node.h"
#include "node/parse.h"
#include "timer.h"

class RW;
class Window;

Entity::Entity() { uid = static_cast<long>(reinterpret_cast<intptr_t>(this)); }

Entity::Entity(std::string path, Window &window, int x, int y, int w, int h) {
	sprite.from_sheet(path, window, w, h, 0);
	sprite.rect.set_x_velocity(0);
	sprite.rect.set_y_velocity(0);
	sprite.rect.set_position(x, y);
	sprite.rect.set_dimensions(w, h);
	uid = static_cast<long>(reinterpret_cast<intptr_t>(this));
}

Entity::Entity(RW &, SDL_Renderer *, int x, int y) {
	sprite.rect.set_velocities(0, 0);
	sprite.rect.set_position(x, y);
	uid = static_cast<long>(reinterpret_cast<intptr_t>(this));
}

void Entity::read_script(std::string path) {
	std::ifstream script_file(path, std::ios::in | std::ios::binary);
	if (script_file) {
		script_file.seekg(0, std::ios::end);
		script_contents.resize(script_file.tellg());
		script_file.seekg(0, std::ios::beg);
		script_file.read(&script_contents[0], script_contents.size());
		script_file.close();
	}
}

std::string Entity::get_name() { return name; }

void Entity::set_rate(const int rate) { this->rate = rate; }

void Entity::move(int constraint_x, int constraint_y, Timer &timer) {
	if (timer.is_paused()) {
		return;
	}
	if (timer.get_ticks() > (last_time + rate)) {
		sprite.rect.set_x_cord(sprite.rect.get_x_cord() +
				       (sprite.rect.get_x_velocity()));
		sprite.rect.set_y_cord(sprite.rect.get_y_cord() +
				       (sprite.rect.get_y_velocity()));
		last_time = timer.get_ticks();
	}
	if ((sprite.rect.get_x_cord() < 0) ||
	    (sprite.rect.get_x_cord() + sprite.rect.get_width() >
	     constraint_x)) {
		sprite.rect.set_x_cord(sprite.rect.get_x_cord() -
				       sprite.rect.get_x_velocity());
	}

	if ((sprite.rect.get_y_cord() < 0) ||
	    (sprite.rect.get_y_cord() + sprite.rect.get_height() >
	     constraint_y)) {
		sprite.rect.set_y_cord(sprite.rect.get_y_cord() -
				       sprite.rect.get_y_velocity());
	}
}

Entity &Entity::operator=(const Entity &copy) {
	last_time = copy.last_time;
	sprite = copy.sprite;
	rate = copy.rate;
	uid = copy.uid;
	name = copy.name;
	script = copy.script;
	script_contents = copy.script_contents;
	return *this;
}

Entity::Entity(const Entity &copy) {
	last_time = copy.last_time;
	sprite = copy.sprite;
	rate = copy.rate;
	uid = copy.uid;
	name = copy.name;
	script = copy.script;
	script_contents = copy.script_contents;
}

int Entity::get_uid() { return uid; }

Sprite &Entity::get_sprite() { return sprite; }

void Entity::yaml_attributes(std::string path) {
	YAML::Node from = YAML::LoadFile(path);
	if (from["attributes"]) {
		std::for_each(
		    from["attributes"].begin(), from["attributes"].end(),
		    [this](YAML::Node attributes) {
			    this->attributes_map[attributes["name"]
						     .as<std::string>()] =
				attributes["value"].as<std::string>();
		    });
	}
}

void Entity::debug_log(DebugLog &log) {
	log << "Entity: " << uid << " created\n";
}
