#include <SDL.h>
#include <stdio.h>
#include "kuma.h"

using namespace kuma;
int main(int, char *[]) {
	Game kuma("data/meta/game.yaml");
	kuma.global_script_context.open_script("src/scripts/test_main.lua");
	kuma.global_scene_manager.scenes_from_yaml("res/test_scenes.yaml",
						   kuma.window);
	Music clip("res/sound/Revolve.ogg");

	SDL_Event e;

	Player player;
	player.sprite.from_yaml("res/entities/player.yaml", kuma.window);
	player.sprite.rect.set_dimensions(97, 71);
	player.sprite.rect.set_outline_color(255, 0, 0, 0);
	player.sprite.set_current_animation("standing");
	player.yaml_attributes("res/entities/player_attributes.yaml");
	player.set_rate(3);

	player.debug_log(kuma.debug_log);

	kuma.global_scene_manager.map_front_scene(kuma.window);

	Text display_text("res/LiberationMono-Regular.ttf", 16, kuma.window,
			  kuma.displays.displays.at(0).get_height(), 0, 0);
	display_text.set_text("Press 'Q' to quit and 'Space' to pause",
			      kuma.window);
	display_text.set_color(255, 255, 255, 0);
	kuma.global_mixer.play(clip);
	kuma.global_mixer.set_master_volume(128 / 2);

	while (kuma.is_running()) {
		display_text.set_position(
		    20,
		    kuma.window.get_height() -
			display_text.get_rect().get_height());
		kuma.window.render_frame();
		kuma.global_script_context.execute();
		kuma.global_scene_manager.render_front(
		    kuma.window, kuma.global_timer, kuma.global_mixer);
		// player.sprite.draw_ex(kuma.window, kuma.global_timer,
		// kuma.global_mixer, 45);
		player.sprite.draw(kuma.window, kuma.global_timer,
				   kuma.global_mixer);
		display_text.draw(kuma.window, kuma.global_timer);
		player.sprite.rect.draw(kuma.window);
		kuma.global_scene_manager.scenes.front().map.draw_tile_outlines(
		    kuma.window);
		kuma.global_scene_manager.scenes.front()
		    .entity_map.draw_entity_outlines(kuma.window);
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				kuma.end();
			}
			if (e.type == SDL_KEYDOWN && e.key.repeat == false) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					kuma.global_scene_manager.next_scene(
					    kuma.window, kuma.global_timer,
					    kuma.global_mixer);
					break;
				case SDLK_1:
					kuma.global_scene_manager.prev_scene(
					    kuma.window, kuma.global_timer,
					    kuma.global_mixer);
					break;
				case SDLK_q:
					kuma.end();
					break;
				case SDLK_k:
					kuma.global_mixer.inc_master_volume(32);
					break;
				case SDLK_n:
					break;
				case SDLK_j:
					kuma.global_mixer.dec_master_volume(32);
					break;
				case SDLK_SPACE:
					if (!kuma.global_timer.is_paused()) {
						display_text.set_text(
						    "Press 'Q' to quit and "
						    "'Space' to pause\nPaused",
						    kuma.window);
						kuma.global_timer.pause();
					} else {
						display_text.set_text(
						    "Press 'Q' to quit and "
						    "'Space' to "
						    "pause\nUnpaused",
						    kuma.window);
						kuma.global_timer.unpause();
					}
					if (!kuma.global_mixer.music_paused()) {
						kuma.global_mixer.pause_music();
					} else {
						kuma.global_mixer
						    .resume_music();
					}
					break;
				}
			}
			player.handle_input(kuma.window, e, kuma.global_timer);
		}
		player.move(1000, 1000, kuma.global_timer);
	}
	return 0;
}
