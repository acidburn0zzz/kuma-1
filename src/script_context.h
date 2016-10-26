#ifndef _SCRIPT_CONTEXT_H_
#define _SCRIPT_CONTEXT_H_

#include <fstream>
#include "luawrapper/LuaContext.hpp"

class ScriptContext : public LuaContext {
public:
	void open_script(std::string path);
	void execute();
	ScriptContext &operator=(const ScriptContext &copy);

private:
	std::string inner_script;
};

#endif
