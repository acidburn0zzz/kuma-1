#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"
#include "texture.h"

class Player : public Entity {
public:
	using Entity::Entity;
	Player();
	void handle_input(Window &window, const SDL_Event &event, Timer &timer);
	unsigned last_time = 0;
};

#endif // _PLAYER_H_
