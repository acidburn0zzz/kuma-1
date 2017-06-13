#include "scene_manager.h"

#include "node/impl.h"
#include "node/node.h"
#include "node/parse.h"
#include "scene.h"

using namespace kuma;
class Window;

SceneManager::SceneManager() {}

void SceneManager::add(Scene scene) { scenes.push_back(scene); }

void SceneManager::clear() {
	while (scenes.size() != 0) {
		scenes.pop_front();
	}
}

void SceneManager::scenes_from_yaml(const std::string path, Window &window) {
	read_yaml(path, window);
}

void SceneManager::read_yaml(std::string path, Window &window) {
	YAML::Node from = YAML::LoadFile(path);
	for (auto it = from.begin(); it != from.end(); ++it) {
		scenes.push_back(Scene());
		if (it->second["order"]) {
			scenes.back().order = it->second["order"].as<int>();
		}
		if (it->second["name"]) {
			scenes.back().name =
			    it->second["name"].as<std::string>();
		}
		if (it->second["map"]) {
			scenes.back().map.from_yaml(
			    it->second["map"].as<std::string>(), window);
		}
		if (it->second["entity_map"]) {
			scenes.back().entity_map.from_yaml(
			    it->second["entity_map"].as<std::string>(), window);
		}
	}
	std::sort(scenes.begin(), scenes.end(),
		  [](Scene &lh, Scene &rh) { return lh.order < rh.order; });
}

void SceneManager::map_front_scene(Window &window) {
	if (!scenes.empty()) {
		scenes.front().map.map_tiles(window);
		scenes.front().entity_map.map_entities(window);
	}
}

void SceneManager::render_front(Window &window, Timer &timer, Mixer &mixer) {
	if (!scenes.empty()) {
		scenes.front().map.draw(window);
		scenes.front().entity_map.draw_entity_outlines(window);
		scenes.front().entity_map.draw(window, timer, mixer);
	}
}

void SceneManager::pop_scene(Window &window) {
	if (!scenes.empty()) {
		scenes.pop_front();
	}
	if (!scenes.empty()) {
		map_front_scene(window);
	}
}

void SceneManager::next_scene(Window &window, Timer &timer, Mixer &mixer) {
	scenes.push_back(scenes.front());
	scenes.pop_front();
	render_front(window, timer, mixer);
}

void SceneManager::prev_scene(Window &window, Timer &timer, Mixer &mixer) {
	scenes.push_front(scenes.back());
	scenes.pop_back();
	render_front(window, timer, mixer);
}
