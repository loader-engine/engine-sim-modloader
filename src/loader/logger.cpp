
#include "../../include/loader/logger.h"

Logger::Logger()
{

}

void Logger::Initialize()
{
	//coutFile = std::ofstream("cout.txt");
}

void Logger::Finalize()
{
	//coutFile.close();
}

void Logger::Debug(std::string message)
{
	OutputDebugStringA(message.c_str());
	printf(message.c_str());
	//coutFile << cstr;
}

void Logger::DebugLine(std::string message)
{
	Debug(message + "\n");
}