#ifndef _log_h_
#define _log_h_

#include <fstream>
#include <iostream>
#include <string>

class DebugLoggable;

class Log {
public:
	Log(){};
	Log(std::string path);
};

class DebugLog {
public:
	DebugLog(){};
	DebugLog(std::string path);
	~DebugLog() { inner_log_file.close(); };
	void open(std::string path);
	std::ofstream &log_file();
	template <class T> DebugLog &operator<<(const T &line) {
		inner_log_file << line;
		return *this;
	}

private:
	std::ofstream inner_log_file;
};

class DebugLoggable {
public:
	virtual void debug_log(DebugLog &log) = 0;
};

#endif
