#ifndef DDEV_LOGGER_H
#define DDEV_LOGGER_H

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

#include <windows.h>

class Logger {
public:
	Logger();

public:

	static void Debug(std::string message);
	static void DebugLine(std::string message);

};

#endif
