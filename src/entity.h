#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SDL.h>
#include <fstream>
#include <iostream>
#include <yaml.h>
#include "log.h"
#include "rect.h"
#include "rw.h"
#include "script_context.h"
#include "sprite.h"
#include "window.h"

class Entity : public DebugLoggable {
public:
	Entity();
	Entity(std::string path, Window &window, int x, int y, int w, int h);
	Entity(RW &rw, SDL_Renderer *ren, int x, int y);
	void execute_script(std::string name, std::string path,
			    ScriptContext &context);
	void load_script(std::string path, ScriptContext &context);
	void yaml_attributes(std::string path);
	void move(int constraint_x, int constraint_y, Timer &timer);
	void render(Window &window, Timer &timer);
	void set_rate(const int rate);
	void debug_log(DebugLog &log);
	int get_uid();
	int x_vel, y_vel;
	Sprite &get_sprite();
	Entity(const Entity &copy);
	Entity &operator=(const Entity &copy);
	void write_variables(ScriptContext &context);
	std::string get_name();
	Sprite sprite;
	std::map<std::string, std::string> attributes_map;
	int rate;

private:
	unsigned last_time = 0;
	int uid;
	int life;
	int damage;
	std::string name;
	void read_script(std::string path);
	ScriptContext script;
	std::string script_contents;
};

#endif // _ENTITY_H_
