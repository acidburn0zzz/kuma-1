#include "entity_manager.h"

EntityManager::EntityManager() {}

void EntityManager::add(Entity &entity) {
	database.insert(std::pair<int, Entity &>(entity.get_uid(), entity));
}

void EntityManager::remove(Entity &entity) {
	// for (auto it = database.begin(); it != database.end();) {
	// if (it->first == entity.get_uid()) {
	// it = database.erase(it);
	// entity.texture.get_texture().free();
	//} else {
	//++it;
	//}
	//}
}

void EntityManager::clear() { database.clear(); }

void EntityManager::render_all(Window &window) {
	// for (auto it = database.cbegin(); it != database.cend(); it++) {
	// if (it->second.sprite.sheet.texture.get_sdl_texture() != nullptr) {
	// window.render(it->second.sprite.sheet, it->second.get_rect());
	//}
	//}
}

EntityManager &EntityManager::operator=(const EntityManager &copy) {
	database = copy.database;
	return *this;
}
