#include "entity_map.h"

EntityMap::EntityMap() {}

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
	if (from["empty_h"]) {
		entity_layer.empty_w = from["empty_w"].as<int>();
	}
	if (from["legend"]) {
		for (unsigned i = 0; i < from["legend"].size(); i++) {
			entity_layer.legend.insert(
			    std::pair<char, std::tuple<std::string, std::string,
						       int, int>>(
				from["legend"][i]["key"].as<char>(),
				std::make_tuple(
				    from["legend"][i]["image"]
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
			auto entity = entity_layer.legend.find(*it);
			if (entity != entity_layer.legend.end()) {
				entities.emplace_back(new Entity(
				    std::get<0>(entity->second), window, x, y,
				    std::get<2>(entity->second),
				    std::get<3>(entity->second)));

				x = x +
				    entities.back()
					->get_sprite()
					.sheet.clip_width;

				entities.back()->yaml_attributes(
				    std::get<1>(entity->second));
			}
		}
		if (*it == '\n') {
			y = y + entity_layer.empty_h;
			x = 0;
		}
		if (*it == entity_layer.empty) {
			x = x + entity_layer.empty_w;
		}
	}
}

void EntityMap::draw_entity_outlines(Window &window) {
	for (auto it = entities.begin(); it != entities.end(); ++it) {
		it->get()->sprite.rect.draw(window);
	}
}

void EntityMap::draw(Window &window) {
	for (auto it = entities.begin(); it != entities.end(); ++it) {
		it->get()->sprite.draw(window);
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
