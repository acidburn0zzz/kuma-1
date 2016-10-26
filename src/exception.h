#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>

class KException : public std::exception {
private:
	std::string inner_msg;

public:
	KException(const std::string &msg) : inner_msg(msg){};
	virtual const char *what() const throw() { return inner_msg.c_str(); }
};

#endif
