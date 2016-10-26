#include "util.h"

bool file_exists(std::string path) {
	std::ifstream f(path);
	return f.good();
}
