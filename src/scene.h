#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>

#include "cereal/archives/json.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include "entity_map.h"
#include "map.h"
#include "script_context.h"

namespace kuma {
	class Scene {
	public:
		Scene();
		Scene(const Scene &copy);
		Scene &operator=(const Scene &copy);
		void end();
		int order = 0;

		std::string name;
		EntityMap entity_map;
		Map map;
		ScriptContext scene_context;
		template <class Archive> void serialize(Archive &ar) {
			ar(CEREAL_NVP(order));
			ar(CEREAL_NVP(name));
			ar(CEREAL_NVP(entity_map));
			ar(CEREAL_NVP(map));
		}
	};
}

#endif // _SCENE_H_
