#ifndef _POSABLE_H_
#define _POSABLE_H_

#include "rect.h"

namespace kuma {
	class Posable {
	public:
		virtual Rect &get_rect() = 0;
	};
}

#endif // _POSABLE_H_
