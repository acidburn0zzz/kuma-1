#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../src/kuma.h"

#include <tuple>

TEST_CASE("OK", "OK") {
	Init init(InitFlag::InitTimer, ImgInitFlag::InitPng);
	Window window("Test", 0, 0, 100, 100);
}
