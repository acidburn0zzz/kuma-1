#ifndef _LAYER_H_
#define _LAYER_H_

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <yaml.h>

#include "entity.h"
#include "tile.h"

namespace kuma {
	class TileLayer {
	public:
		int level;
		std::string name;
		std::map<char, std::string> legend;
		std::string raw;
		char empty;
		int empty_h;
		int empty_w;
		TileLayer &operator=(const TileLayer &copy);
		std::vector<Tile> tiles;
	};

	class EntityLayer {
	public:
		std::map<char, std::tuple<std::string, std::string, int, int>>
		    legend;
		std::string raw;
		char empty;
		int empty_h;
		int empty_w;
		EntityLayer &operator=(const EntityLayer &copy);
	};
}

#endif // _LAYER_H_
