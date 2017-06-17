#include "config.h"

#include <fstream>

#include "display.h"
#include "node/node.h"

using namespace kuma;

void Config::from_yaml(std::string path) {
	YAML::Node from = YAML::LoadFile(path);
	Displays displays;
	if (from["window_height"]) {
		if (from["window_height"].as<std::string>() == "default") {
			window_height = displays.displays.at(0).get_height();
		} else {
			window_height = from["window_height"].as<int>();
		}
	}
	if (from["window_width"]) {
		if (from["window_width"].as<std::string>() == "default") {
			window_width = displays.displays.at(0).get_width();
		} else {
			window_width = from["window_width"].as<int>();
		}
	}
	if (from["window_flag"]) {
		if (from["window_flag"].as<std::string>() == "fullscreen") {
			window_flag = WindowFlag::Fullscreen;
		}
		if (from["window_flag"].as<std::string>() == "borderless") {
			window_flag = WindowFlag::Borderless;
		}
		if (from["window_flag"].as<std::string>() == "windowed") {
			window_flag = WindowFlag::Shown;
		}
		if (from["window_flag"].as<std::string>() == "minimized") {
			window_flag = WindowFlag::Minimized;
		}
		if (from["window_flag"].as<std::string>() == "maximized") {
			window_flag = WindowFlag::Maximized;
		}
		if (from["window_flag"].as<std::string>() == "hidden") {
			window_flag = WindowFlag::Hidden;
		}
	}
}

void Config::new_config(std::string path) {
	path += "config.yaml";
	if (!file_exists(path)) {
		std::fstream file(path, std::fstream::out);
		file << "---\n"
		     << "window_height: default\n"
		     << "window_width: default\n"
		     << "window_flag: windowed\n"
		        "...\n";
		file.close();
	}
}
