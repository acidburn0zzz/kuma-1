#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include <algorithm>
#include <deque>
#include <yaml.h>

#include "exception.h"
#include "scene.h"
#include "window.h"

class SceneManager {
public:
	SceneManager();
	void add(Scene scene);
	void scenes_from_yaml(const std::string path, Window &window);
	void clear();
	void from_yaml(std::string, Window &window);
	void read_yaml(std::string path, Window &window);
	void map_front_scene(Window &window);
	void render_front(Window &window);
	void pop_scene(Window &window);
	void next_scene(Window &window);
	void prev_scene(Window &window);
	std::deque<Scene> scenes;
};

#endif // _SCENE_MANAGER_H_
