#include "layer.h"
using namespace kuma;

TileLayer &TileLayer::operator=(const TileLayer &copy) {
	level = copy.level;
	name = copy.name;
	legend = copy.legend;
	raw = copy.raw;
	empty = copy.empty;
	empty_h = copy.empty_h;
	empty_w = copy.empty_w;
	return *this;
}

EntityLayer &EntityLayer::operator=(const EntityLayer &copy) {
	legend = copy.legend;
	raw = copy.raw;
	empty = copy.empty;
	empty_h = copy.empty_h;
	empty_w = copy.empty_w;
	return *this;
}
