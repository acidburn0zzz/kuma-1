#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <fstream>
#include <yaml.h>

#include "util.h"
#include "window.h"

class Config {
public:
	Config() {}
	void from_yaml(std::string path);
	void new_config(std::string path);
	int window_width;
	int window_height;
	WindowFlag window_flag;
};

#endif // _CONFIG_H_
