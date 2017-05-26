#include <typeinfo>
#include <iostream>

#include "entity_map.h"

EntityMap::EntityMap() {
	entity_layer = EntityLayer();
}

void EntityMap::from_yaml(std::string path, Window &window) {
	read_yaml(path);
	map_entities(window);
}

void EntityMap::read_yaml(std::string path) {
	YAML::Node from = YAML::LoadFile(path);
	if (from["empty"]) {
		entity_layer.empty = from["empty"].as<char>();
	}
	if (from["empty_h"]) {
		entity_layer.empty_h = from["empty_h"].as<int>();
	}
	if (from["empty_w"]) {
		entity_layer.empty_w = from["empty_w"].as<int>();
	}
	if (from["legend"]) {
		for (unsigned i = 0; i < from["legend"].size(); i++) {
			entity_layer.legend.insert(
			    std::pair<char, std::tuple<std::string, std::string,
						       int, int>>(
				from["legend"][i]["key"].as<char>(),
				std::make_tuple(
				    from["legend"][i]["sprite_yaml"]
					.as<std::string>(),
				    from["legend"][i]["attributes"]
					.as<std::string>(),
				    from["legend"][i]["w"].as<int>(),
				    from["legend"][i]["h"].as<int>())));
		}
	}
	if (from["raw"]) {
		entity_layer.raw = from["raw"].as<std::string>();
	}
}

void EntityMap::map_entities(Window &window) {
	int x = 0, y = 0;
	for (auto it = entity_layer.raw.begin(); it != entity_layer.raw.end();
	     ++it) {
		if ((*it != '\n') && (*it != entity_layer.empty)) {
			auto entity_entry = entity_layer.legend.find(*it);
			if (entity_entry != entity_layer.legend.end()) {
				entities.emplace_back(new Entity);
				entities.back()->sprite.from_yaml(
				    std::get<0>(entity_entry->second), window);
				entities.back()->sprite.rect.set_x_cord(x);
				entities.back()->sprite.rect.set_y_cord(y);
				x += entities.back()
					 ->get_sprite()
					 .sheet.clip_width;
				entities.back()->yaml_attributes(
				    std::get<1>(entity_entry->second));
			}
		}
		if (*it == '\n') {
			y += entity_layer.empty_h;
			x = 0;
		}
		if (*it == entity_layer.empty) {
			x += entity_layer.empty_w;
		}
	}
}

void EntityMap::draw_entity_outlines(Window &window) {
	for (auto it = entities.begin(); it != entities.end(); ++it) {
		it->get()->sprite.rect.draw(window);
	}
}

void EntityMap::draw(Window &window, Timer &timer, Mixer &mixer) {
	for (auto it = entities.begin(); it != entities.end(); ++it) {
		it->get()->sprite.draw(window, timer, mixer);
	}
}

EntityMap &EntityMap::operator=(const EntityMap &copy) {
	entities = copy.entities;
	entity_layer = copy.entity_layer;
	return *this;
}

EntityMap::EntityMap(const EntityMap &copy) {
	entities = copy.entities;
	entity_layer = copy.entity_layer;
}
