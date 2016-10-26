#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <map>

#include "entity.h"
#include "script_context.h"
#include "window.h"

class EntityManager {
public:
	EntityManager();
	void add(Entity &entity);
	void remove(Entity &entity);
	void clear();
	void render_all(Window &window);
	void write_variables(ScriptContext &context);
	int total_texture_size;
	EntityManager &operator=(const EntityManager &copy);

private:
	std::multimap<int, Entity &> database;
};

#endif
