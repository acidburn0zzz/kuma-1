#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>

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
	};
}

#endif // _SCENE_H_
