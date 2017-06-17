#ifndef _MAP_H_
#define _MAP_H_

#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <yaml.h>

#include "cereal/access.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include "drawable.h"
#include "layer.h"
#include "texture.h"
#include "tile.h"
#include "window.h"

namespace kuma {
	class Window;

	class Map : public Drawable {
	public:
		Map();
		Map(std::string, Window &window);
		void from_yaml(std::string path, Window &window);
		void map_tiles(Window &window);
		void read_yaml(std::string path);
		void draw_tile_outlines(Window &window);
		void draw(Window &window);
		std::string name;
		Map &operator=(const Map &copy);

		friend class cereal::access;
		template <class Archive> void serialize(Archive &ar) {
			ar(CEREAL_NVP(name));
			ar(CEREAL_NVP(layers));
		}

	private:
		void sort_layers();
		std::string yaml_file_name;
		std::vector<TileLayer> layers;
	};
}

#endif // _MAP_H_
