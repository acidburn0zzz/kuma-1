#include "log.h"

using namespace kuma;
DebugLog::DebugLog(std::string path) { inner_log_file.open(path, std::fstream::out); }

void DebugLog::open(std::string path) { inner_log_file.open(path, std::fstream::out); }

std::ofstream &DebugLog::log_file() { return inner_log_file; }
