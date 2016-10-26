#ifndef _ENTITY_MAP_H_
#define _ENTITY_MAP_H_

#include <map>
#include <tuple>
#include <yaml.h>

#include "entity.h"
#include "layer.h"
#include "window.h"

class EntityMap {
public:
	EntityMap();
	void from_yaml(std::string path, Window &window);
	void read_yaml(std::string path);
	void map_entities(Window &window);
	void draw(Window &window);
	void draw_entity_outlines(Window &window);
	EntityMap &operator=(const EntityMap &copy);
	EntityMap(const EntityMap &copy);

	std::vector<std::shared_ptr<Entity>> entities;
	EntityLayer entity_layer;
};

#endif
