#include "user_files.h"

UserFiles::UserFiles(std::string org_name, std::string game_name) {
	set_dir(org_name, game_name);
}

void UserFiles::set_dir(std::string org_name, std::string game_name) {
	char *base = SDL_GetPrefPath(org_name.c_str(), game_name.c_str());
	save_dir = std::string(base, strlen(base));
	SDL_free(base);
}

void UserFiles::create_dir() {
	struct stat buffer;
	if (stat(save_dir.c_str(), &buffer) != 0) {
#ifdef __unix__
		mkdir(save_dir.c_str(), S_IRWXU);
#else
		mkdir(save_dir.c_str());
#endif
	}
}

std::string UserFiles::get_path() { return save_dir; }
