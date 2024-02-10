#include "Logger.h"
#include <iostream>
#include <sstream>

static const char* logPath;
static std::FILE* fp;

static bool toFile = false;
static bool toConsole = false;
static uint32_t allowedSeverity(DEFAULT_SEV);

void Logger::SetLogDest(int destFlags)
{
	toFile = destFlags & DEST_FILE;
	toConsole = destFlags & DEST_CONSOLE;
}

void Logger::InitLog(const std::string& logPath, LogLevel level, int destFlags) {
	SetLogDest(destFlags);

	if (logPath.size())
	{
		fopen_s(&fp, logPath.c_str(), "w");
		if (fp == NULL)
		{
			LOG_WARN("Failed to create log file, bad file path");
		}
	}
	LOG_INFO("Initialized Logger");
}

void Logger::SetLogLevel(uint32_t allowedSev)
{
	allowedSev = allowedSev;
}

/**
* Main logic for handling logging args
* Format specifiers:
*		-d = int
*       -f = double
*       -c = char
*       -s = string
*
* @todo Move entrance call to macro to allow for error location information
*/
void Logger::Log(const std::string& sev_msg, const std::string& filename, const std::string& funcName, int lineNum, LogLevel level, const char* msg, ...) {
	if (!(level & allowedSeverity))
		return;

	std::stringstream stream;
	std::string buff(sev_msg + "-" + filename + ":" + funcName + ":" + std::to_string(lineNum) + " - ");
	int next = buff.size();
	buff.resize(512);
	va_list args;
	va_start(args, msg);

	bool formatModifier = false; // true if the next char is for defining a var format
	while (*msg != '\0') {
		if (next / buff.size() > 0.5)
		{
			buff.resize(buff.size() * 2);
		}

		if (*msg == '%') { formatModifier = true; }

		else if (formatModifier) {

			switch (*msg) {
			case 'd':
			{
				int i = va_arg(args, int);
				next += sprintf(&buff[next], "%d", i);
				break;
			}

			case 'f':
			{
				double f = va_arg(args, double);
				next += sprintf(&buff[next], "%f", f);
				break;
			}

			case 'c':
			{
				int c = va_arg(args, int);
				next += sprintf(&buff[next], "%c", c);
				break;
			}

			case 's':
			{
				char* s = va_arg(args, char*);
				next += sprintf(&buff[next], "%s", s);
				break;
			}

			default:
			{
				LOG_WARN("Unrecognizable printf format specificer");
				return;
			}

			}
			formatModifier = false;
		}

		else {
			next += sprintf(&buff[next], "%c", *msg);
		}

		++msg;
	}

	if (toConsole)
	{
		LogPrint(buff.c_str(), level);
	}

	if (toFile)
	{
		LogFile(buff.c_str());
	}
}

inline void Logger::LogPrint(const char* msg, LogLevel sev) {
	if (sev < SEV_WARN)
	{
		std::cout << msg << std::endl;
	}
	else
	{
		std::cerr << msg << std::endl;
	}
}

inline void Logger::LogFile(const char* msg) {
	fprintf(fp, "%s", &msg[0]);
}