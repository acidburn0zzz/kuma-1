#include "scene.h"

using namespace kuma;
Scene::Scene() {}

Scene::Scene(const Scene &copy) {
	name = copy.name;
	order = copy.order;
	entity_map = copy.entity_map;
	map = copy.map;
	scene_context = copy.scene_context;
}

Scene &Scene::operator=(const Scene &copy) {
	name = copy.name;
	order = copy.order;
	entity_map = copy.entity_map;
	map = copy.map;
	scene_context = copy.scene_context;
	return *this;
}
