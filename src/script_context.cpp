#include "script_context.h"

#include <fstream>

void ScriptContext::open_script(std::string script) {
	open_libraries();
	std::string script_contents;
	std::ifstream script_file(script, std::ios::in | std::ios::binary);

	if (script_file) {
		script_file.seekg(0, std::ios::end);
		script_contents.resize(script_file.tellg());
		script_file.seekg(0, std::ios::beg);
		script_file.read(&script_contents[0], script_contents.size());
		script_file.close();
	}
	inner_script = script_contents;
}

void ScriptContext::execute() { script(inner_script); }

ScriptContext &ScriptContext::operator=(const ScriptContext &copy) {
	inner_script = copy.inner_script;
	return *this;
}
