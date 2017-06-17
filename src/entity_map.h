#ifndef _ENTITY_MAP_H_
#define _ENTITY_MAP_H_

#include <map>
#include <string>
#include <tuple>
#include <yaml.h>

#include "cereal/archives/json.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include "entity.h"
#include "layer.h"
#include "window.h"

namespace kuma {
	class Mixer;
	class Timer;
	class Window;

	class EntityMap {
	public:
		EntityMap();
		void from_yaml(std::string path, Window &window);
		void read_yaml(std::string path);
		void map_entities(Window &window);
		void draw(Window &window, Timer &timer, Mixer &mixer);
		void draw_entity_outlines(Window &window);
		EntityMap &operator=(const EntityMap &copy);
		EntityMap(const EntityMap &copy);

		std::vector<std::shared_ptr<Entity>> entities;
		EntityLayer entity_layer;
		template <class Archive> void serialize(Archive &ar) {
			ar(CEREAL_NVP(entity_layer));
		}
	};
}

#endif
