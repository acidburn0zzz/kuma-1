#include "flip.h"

using namespace kuma;

void Flippable::flip_vertical() {
	if (orientation != Flip::Vertical) {
		orientation = Flip::Vertical;
	} else {
		orientation_reset();
	}
}

void Flippable::flip_horizontal() {
	if (orientation != Flip::Horizontal) {
		orientation = Flip::Horizontal;
	} else {
		orientation_reset();
	}
}

void Flippable::flip_diagonal() {
	if (orientation != Flip::Diagonal) {
		orientation = Flip::Diagonal;
	} else {
		orientation_reset();
	}
}

void Flippable::orientation_reset() {
	if (orientation != Flip::None) {
		orientation = Flip::None;
	}
}

Flip &Flippable::get_orientation() { return orientation; }
