#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <fstream>
#include <string>
#include <yaml.h>

#include "util.h"
#include "window.h"

namespace kuma {
	class Config {
	public:
		Config() {}
		void from_yaml(std::string path);
		void new_config(std::string path);
		int window_width = 0;
		int window_height = 0;
		WindowFlag window_flag = WindowFlag::Shown;
	};
}

#endif // _CONFIG_H_
