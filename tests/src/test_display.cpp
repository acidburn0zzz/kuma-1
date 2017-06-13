#define CATCH_CONFIG_MAIN

#include "../src/kuma.h"
#include "catch.hpp"

using namespace kuma;

Window window("Test", 0, 0, 100, 100);

TEST_CASE("Init", "OK") {
	Init init(InitFlag::InitTimer, ImgInitFlag::InitPng);
	CHECK(init.set_init_flag == InitFlag::InitTimer);
	CHECK(init.set_img_init_flag == ImgInitFlag::InitPng);
}

TEST_CASE("SpriteSheet", "[SpriteSheet]") {
	SpriteSheet sheet("../res/prehistoric-platformer/characters/npc/dragon-man.png", window, 58, 67);
	REQUIRE(sheet.clip_height() == 67);
	REQUIRE(sheet.clip_width() == 58);
	REQUIRE(sheet.clip_margin() == 0);
	REQUIRE(sheet.cells.size() == 10);
	REQUIRE(sheet.all.get_dimensions() == std::make_tuple(290, 134));
	REQUIRE(sheet.texture.get_sdl_texture() != nullptr);
}

TEST_CASE("Animation", "[Animation] [SpriteSheet] [Rect]") {
	SpriteSheet sheet("../res/prehistoric-platformer/characters/npc/dragon-man.png", window, 58, 67);
	Rect rect(0, 0, 58, 67);
	Animation animation("Test Animation", 10);
	for (int i = 1; i <= 10; i++) {
		animation.frames.push_back(sheet.cells[i]);
	}
	animation.render_front(window, sheet.texture, rect);
	window.render_frame();
}
