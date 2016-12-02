#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include "flip.h"

class Window;
class Timer;
class Mixer;

class Drawable : public Flippable {
public:
	virtual void draw(Window &window) = 0;
};

class AnimatedDrawable : public Flippable {
public:
	virtual void draw(Window &window, const Timer &timer) = 0;
	virtual void draw(Window &, const Timer &, Mixer &){};
	virtual void draw_ex(Window &, const Timer &, Mixer &, double){};
	// virtual void draw_ex(Window &window, const Timer &timer, const int
	// angle,
};

#endif
