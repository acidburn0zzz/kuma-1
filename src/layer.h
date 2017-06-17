#ifndef _LAYER_H_
#define _LAYER_H_

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <yaml.h>

#include "cereal/archives/json.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include "entity.h"
#include "tile.h"

namespace kuma {
	class TileLayer {
	public:
		int level;
		std::string name;
		std::map<std::string, std::string> legend;
		std::string raw;
		char empty;
		int empty_h;
		int empty_w;
		TileLayer &operator=(const TileLayer &copy);
		std::vector<Tile> tiles;
		template <class Archive> void serialize(Archive &ar) {
			ar(CEREAL_NVP(name));
			ar(CEREAL_NVP(legend));
			ar(CEREAL_NVP(raw));
			ar(CEREAL_NVP(empty));
			ar(CEREAL_NVP(empty_h));
			ar(CEREAL_NVP(empty_w));
			ar(CEREAL_NVP(tiles));
		}
	};

	class EntityLayerEntry {
	public:
		EntityLayerEntry(){};
		EntityLayerEntry(std::string s, std::string a, int w, int h) {
			this->sprite_yaml = s;
			this->attributes = a;
			this->w = w;
			this->h = h;
		}
		std::string sprite_yaml;
		std::string attributes;
		int w;
		int h;
		template <class Archive> void serialize(Archive &ar) {
			ar(CEREAL_NVP(sprite_yaml));
			ar(CEREAL_NVP(attributes));
			ar(CEREAL_NVP(w));
			ar(CEREAL_NVP(h));
		}
		EntityLayerEntry &operator=(const EntityLayerEntry &copy) {
			sprite_yaml = copy.sprite_yaml;
			attributes = copy.attributes;
			w = copy.w;
			h = copy.h;
			return *this;
		}
	};

	class EntityLayer {
	public:
		std::map<std::string, EntityLayerEntry> legend;
		std::string raw;
		char empty;
		int empty_h;
		int empty_w;
		EntityLayer &operator=(const EntityLayer &copy);
		template <class Archive> void serialize(Archive &ar) {
			ar(CEREAL_NVP(raw));
			ar(CEREAL_NVP(legend));
			ar(CEREAL_NVP(empty));
			ar(CEREAL_NVP(empty_w));
			ar(CEREAL_NVP(empty_h));
		}
	};
}

#endif // _LAYER_H_
