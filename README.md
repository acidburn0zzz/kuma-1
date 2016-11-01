# kuma: 2D game engine
`kuma` is a 2D game engine being written in C++

## Status
`kuma` is currently not ready for use and is still under development.

### Documentation
Documentation is generated using `Doxygen` and is available by running `make doc`.
All generated documentation is available in `doc/html`

### Dependencies
`kuma` depends on SDL2, SDL2_ttf, SDL2_img, SDL2_mixer, libyaml-cpp, and Lua >= 5.1. `kuma` also uses
[`ThePhD/sol2`](https://github.com/ThePhD/sol2).

### Building

To build a static library version of kuma you can run `make -f
Makefile-static`.  The current `Makefile` is used mainly for testing various
aspects of `kuma`.

### Testing
All tests for `kuma` live in the `tests` directory. To run tests you must first
build `kuma` as a static lib using `make -f Makefile-static` then proceed to
build the tests using `make` and `make run` within the `tests` directory.
