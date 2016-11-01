#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include "audio/mixer.h"
#include "timer.h"
#include "window.h"

class Drawable : public Flippable {
public:
	virtual void draw(Window &window) = 0;
	virtual void draw_ex(Window &){};
};

class AnimatedDrawable : public Flippable {
public:
	virtual void draw(Window &window, const Timer &timer) = 0;
	virtual void draw(Window &, const Timer &, Mixer &){};
	virtual void draw_ex(Window &, const Timer &, Mixer &, double) {};
	// virtual void draw_ex(Window &window, const Timer &timer, const int
	// angle,
};

#endif
