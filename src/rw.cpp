#include "rw.h"

struct SDL_RWops;
using namespace kuma;

void RW::from_mem(void *mem) {
	inner = SharedRWPtr(SDL_RWFromMem(mem, sizeof(mem)));
}

void RW::from_mem(const void *mem) {
	inner = SharedRWPtr(SDL_RWFromConstMem(mem, sizeof(mem)));
}

void RW::from_file(std::string path, std::string mode) {
	inner = SharedRWPtr(SDL_RWFromFile(path.c_str(), mode.c_str()));
}

SDL_RWops *RW::get() { return inner.get(); }

RW &RW::operator=(const RW &copy) {
	inner = copy.inner;
	return *this;
}

RW::RW(const RW &copy) { inner = copy.inner; }
