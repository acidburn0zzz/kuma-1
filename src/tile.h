#ifndef _TILE_H_
#define _TILE_H_

#include <string>

#include "cereal/archives/json.hpp"
#include "cereal/cereal.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include "drawable.h"
#include "rect.h"
#include "texture.h"

namespace kuma {
	class Window;

	class Tile : public Drawable {
	public:
		Tile(std::string, Window &window, int, int);
		Tile(Texture &texture, int, int);
		Texture texture;
		Rect rect;
		void draw(Window &window);
		template <class Archive> void serialize(Archive &ar) { ar(CEREAL_NVP(rect)); }
	};
}

#endif // _TILE_H_
