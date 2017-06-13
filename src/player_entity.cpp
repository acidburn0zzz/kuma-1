#include "player_entity.h"

#include <iostream>
#include <tuple>
using namespace kuma;

Player::Player() {}

void Player::handle_input(Window &, const SDL_Event &event, Timer &) {
	// if (timer.is_paused()) { return; }
	if (event.type == SDL_KEYDOWN && event.key.repeat == false) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			sprite.play_animation("jumping");
			sprite.rect.y_velocity -= 1;
			break;
		case SDLK_s:
			sprite.rect.y_velocity += 1;
			break;
		case SDLK_a:
			sprite.play_animation("running");
			sprite.rect.x_velocity -= 1;
			break;
		case SDLK_d:
			sprite.play_animation("running");
			sprite.rect.x_velocity += 1;
			break;
		}
	} else if (event.type == SDL_KEYUP && event.key.repeat == false) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			sprite.play_animation("standing");
			sprite.rect.y_velocity += 1;
			break;
		case SDLK_s:
			sprite.rect.y_velocity -= 1;
			break;
		case SDLK_a:
			sprite.play_animation("standing");
			sprite.rect.x_velocity += 1;
			break;
		case SDLK_d:
			sprite.play_animation("standing");
			sprite.rect.x_velocity -= 1;
			break;
		}
	}
}
