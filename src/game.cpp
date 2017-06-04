#include "game.h"

#include "node/node.h"

Game::Game(std::string path) {
	YAML::Node from = YAML::LoadFile(path);
	if (from["name"]) {
		name = from["name"].as<std::string>();
	}
	if (from["org"]) {
		org = from["org"].as<std::string>();
	}
	user_files.set_dir(org, name);
	config.new_config(user_files.get_path());
	if (from["user_config"]) {
		auto config_path = user_files.get_path() +=
		    from["user_config"].as<std::string>();
		config.from_yaml(config_path);
	}
	window = Window(
	    name,
	    displays.displays.at(0).get_center_x_cord(config.window_width),
	    displays.displays.at(0).get_center_y_cord(config.window_height),
	    config.window_width, config.window_height, config.window_flag);
	if (from["client_icon"]) {
		window.set_icon(from["client_icon"].as<std::string>());
	}
	this->global_script_context["global_window"] = window;
	window.write_variables(this->global_script_context);
	running = true;
#ifdef _DEBUG_
	debug_log.open(user_files.get_path() + name + "_debug_log.txt");
	std::cout << "Debug log located at '"
		  << user_files.get_path() + name + "_debug_log.txt"
		  << "'\n";
#endif
}

Game::Game(std::string org, std::string name) {
	window =
	    Window(name, 0, 0, displays.displays.at(0).get_width(),
		   displays.displays.at(0).get_height(), WindowFlag::Resizable);
	this->global_script_context["global_window"] = window;
	window.write_variables(this->global_script_context);
	running = true;
	this->name = name;
	this->org = org;
	user_files.set_dir(org, name);
#ifdef _DEBUG_
	debug_log.open(user_files.get_path() + name + "_debug_log.txt");
	std::cout << "Debug log located at '"
		  << user_files.get_path() + name + "_debug_log.txt"
		  << "'\n";
#endif
}

void Game::end() { running = false; }

void Game::run() { running = true; }

bool Game::is_running() { return running; }
