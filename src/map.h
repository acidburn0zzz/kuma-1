#ifndef _MAP_H_
#define _MAP_H_

#include <algorithm>
#include <fstream>
#include <memory>
#include <vector>
#include <yaml.h>

#include "drawable.h"
#include "layer.h"
#include "texture.h"
#include "tile.h"
#include "window.h"

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

private:
	void sort_layers();
	std::string yaml_file_name;
	std::vector<TileLayer> layers;
};

#endif // _MAP_H_
