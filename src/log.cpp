#include "log.h"

DebugLog::DebugLog(std::string path) {
	inner_log_file = std::ofstream(path, std::fstream::out);
}

void DebugLog::open(std::string path) {
	inner_log_file = std::ofstream(path, std::fstream::out);
}

std::ofstream &DebugLog::log_file() { return inner_log_file; }
