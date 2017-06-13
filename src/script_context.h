#ifndef _SCRIPT_CONTEXT_H_
#define _SCRIPT_CONTEXT_H_

#include <fstream>
#include <string>

#include "sol.hpp"

namespace kuma {
	class ScriptContext : public sol::state {
	public:
		void open_script(std::string);
		void execute();
		ScriptContext &operator=(const ScriptContext &);

	private:
		std::string inner_script;
	};
}

#endif
