#include "../src/kuma.h"
#include "catch.hpp"

TEST_CASE("Init", "OK") {
	Init init(InitFlag::InitTimer, ImgInitFlag::InitPng);
	CHECK(init.set_init_flag == InitFlag::InitTimer);
	CHECK(init.set_img_init_flag == ImgInitFlag::InitPng);
}
