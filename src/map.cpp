#include "map.h"

Map::Map() {}

Map::Map(std::string path, Window &window) { from_yaml(path, window); }

void Map::read_yaml(std::string path) {
	YAML::Node from = YAML::LoadFile(path);
	for (YAML::const_iterator it = from.begin(); it != from.end(); ++it) {
		TileLayer temp;
		if (it->second["name"]) {
			temp.name = it->second["name"].as<std::string>();
		}
		if (it->second["level"]) {
			temp.level = it->second["level"].as<int>();
		}
		if (it->second["empty"]) {
			temp.empty = it->second["empty"].as<char>();
		}
		if (it->second["empty_h"]) {
			temp.empty_h = it->second["empty_h"].as<int>();
		}
		if (it->second["empty_h"]) {
			temp.empty_w = it->second["empty_w"].as<int>();
		}
		if (it->second["legend"]) {
			for (unsigned i = 0; i < it->second["legend"].size();
			     i++) {
				temp.legend.insert(std::pair<char, std::string>(
				    it->second["legend"][i]["key"].as<char>(),
				    it->second["legend"][i]["image"]
					.as<std::string>()));
			}
		}
		if (it->second["raw"]) {
			temp.raw = it->second["raw"].as<std::string>();
		}
		layers.push_back(temp);
	}
	sort_layers();
}

void Map::from_yaml(std::string path, Window &window) {
	read_yaml(path);
	yaml_file_name = path;
	map_tiles(window);
}

void Map::sort_layers() {
	std::sort(
	    layers.begin(), layers.end(),
	    [](TileLayer &lh, TileLayer &rh) { return lh.level < rh.level; });
}

void Map::map_tiles(Window &window) {
	for (auto lit = layers.begin(); lit != layers.end(); ++lit) {
		// For each layer reset coordinates
		int x = 0, y = 0;
		// For each char (it) in `raw` string
		for (auto it = lit->raw.cbegin(); it != lit->raw.cend(); ++it) {
			char last = '\n';
			// Not last or `TileLayer.empty`
			if ((*it != '\n') && (*it != lit->empty)) {
				// We have a repeated tile
				if (*it == last) {
					lit->tiles.emplace_back(
					    Tile(lit->tiles.back().texture,
						 lit->tiles.back()
						     .texture.get_width(),
						 lit->tiles.back()
						     .texture.get_height()));
					x += lit->tiles.back()
						 .texture.get_width();
				} else {
					auto tile = lit->legend.find(*it);
					// If tile is found in legend
					if (tile != lit->legend.cend()) {
						// If we have a previous tile
						// then
						// we know how wide it is and
						// can set X
						if (lit->tiles.size() > 0) {
							lit->tiles.emplace_back(
							    Tile(tile->second,
								 window, x, y));
							x += lit->tiles.back()
								 .texture
								 .get_width();
						} else {
							lit->tiles.emplace_back(
							    Tile(tile->second,
								 window, x, y));
							x += lit->empty_w;
						}
					}
				}
				last = *it;
			}
			// char is `TileLayer.empty`
			if (*it == lit->empty) {
				x += lit->empty_w;
				last = lit->empty;
			}
			// End of one line of map
			if (*it == '\n') {
				y += lit->empty_h;
				x = 0;
			}
		}
	}
}

Map &Map::operator=(const Map &copy) {
	layers = copy.layers;
	return *this;
}

void Map::draw(Window &window) {
	for (auto lit = layers.begin(); lit != layers.end(); ++lit) {
		for (auto it = lit->tiles.begin(); it != lit->tiles.end();
		     ++it) {
			window.render(*it, it->rect);
		}
	}
}

void Map::draw_tile_outlines(Window &window) {
	for (auto lit = layers.begin(); lit != layers.end(); ++lit) {
		for (auto it = lit->tiles.begin(); it != lit->tiles.end();
		     ++it) {
			it->rect.draw(window.get_renderer());
		}
	}
}
