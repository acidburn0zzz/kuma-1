#ifndef _USER_FILES_H_
#define _USER_FILES_H_

#include <SDL.h>
#include <sdl_smart_ptr.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>

namespace kuma {
	class UserFiles {
	public:
		UserFiles() {}
		~UserFiles() {}
		UserFiles(std::string org_name, std::string game_name);
		std::string get_path();
		void set_dir(std::string org_name, std::string game_name);
		void create_dir();
		SharedRWPtr rw;

	private:
		std::string save_dir;
	};
}

#endif
