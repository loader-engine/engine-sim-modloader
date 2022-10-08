#ifndef DDEV_LOGGER_H
#define DDEV_LOGGER_H

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>

#include <windows.h>

class Logger {
public:
	Logger();

	//static std::ofstream coutFile;

public:

	static void Initialize();
	static void Finalize();

	static void Debug(std::string message);
	static void DebugLine(std::string message);

};

#endif
