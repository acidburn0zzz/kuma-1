#ifndef _GAME_H_
#define _GAME_H_

#include <yaml.h>

#include "audio/mixer.h"
#include "audio/sound.h"
#include "config.h"
#include "display.h"
#include "init.h"
#include "log.h"
#include "scene_manager.h"
#include "script_context.h"
#include "timer.h"
#include "user_files.h"
#include "window.h"

class Game {
public:
	Game(std::string org, std::string name);
	Game(std::string path);
	DebugLog debug_log;
	Init init;
	Window window;
	Displays displays;
	Config config;
	Timer global_timer;
	Mixer global_mixer;
	ScriptContext global_script_context;
	SceneManager global_scene_manager;
	UserFiles user_files;
	void run();
	void end();
	void from_yaml();
	bool is_running();

private:
	std::string name = "Game Name";
	std::string org = "Organization Name";
	bool running;
};

#endif
