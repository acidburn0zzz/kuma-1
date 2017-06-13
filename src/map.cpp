#include "map.h"

#include "node/impl.h"
#include "node/node.h"
#include "node/parse.h"
using namespace kuma;

class Window;

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
	std::sort(layers.begin(), layers.end(),
		  [](TileLayer &lhs, TileLayer &rhs) {
			  return lhs.level < rhs.level;
		  });
}

void Map::map_tiles(Window &window) {
	for (auto &layer : layers) {
		// For each layer reset coordinates
		int x = 0, y = 0;
		// For each char (tile) in `raw` string
		for (auto &tile : layer.raw) {
			char last = '\n';
			// Not last or `TileLayer.empty`
			if ((tile != '\n') && (tile != layer.empty)) {
				// We have a repeated tile
				if (tile == last) {
					layer.tiles.emplace_back(
					    Tile(layer.tiles.back().texture,
						 layer.tiles.back()
						     .texture.get_width(),
						 layer.tiles.back()
						     .texture.get_height()));
					x += layer.tiles.back()
						 .texture.get_width();
				} else {
					auto tile_entry =
					    layer.legend.find(tile);
					// If tile is found in legend
					if (tile_entry != layer.legend.cend()) {
						// If we have a previous tile
						// then
						// we know how wide it is and
						// can set X
						if (layer.tiles.size() > 0) {
							layer.tiles
							    .emplace_back(Tile(
								tile_entry
								    ->second,
								window, x, y));
							x += layer.tiles.back()
								 .texture
								 .get_width();
						} else {
							layer.tiles
							    .emplace_back(Tile(
								tile_entry
								    ->second,
								window, x, y));
							x += layer.empty_w;
						}
					}
				}
				last = tile;
			}
			// char is `TileLayer.empty`
			if (tile == layer.empty) {
				x += layer.empty_w;
				last = layer.empty;
			}
			// End of one line of map
			if (tile == '\n') {
				y += layer.empty_h;
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
	for (auto &layer : layers) {
		for (auto &tile : layer.tiles) {
			tile.draw(window);
		}
	}
}

void Map::draw_tile_outlines(Window &window) {
	for (auto &layer : layers) {
		for (auto &tile : layer.tiles) {
			tile.rect.draw(window);
		}
	}
}
