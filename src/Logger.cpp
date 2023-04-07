#include "Logger.h"
#include <iostream>
#include <sstream>

// Todo: Make this configurable at some point
#define MAX_BUFF_SIZE 512

static const char* logPath;
static std::FILE* fp;

static bool toFile = false;
static bool toConsole = false;

void Logger::SetLogDest(int destFlags)
{
	toFile = destFlags & DEST_FILE;
	toConsole = destFlags & DEST_CONSOLE;
}


void Logger::InitLog(const char* logPath, int destFlags) {
	SetLogDest(destFlags);

	fp = fopen(logPath, "w");
	if (fp != NULL) {
		printf("Initialized Logger\n");
	}

	else {
		printf("ERROR: Failed to create log file, bad file path\n");
	}
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
void Logger::Log(const char* msg, ...) {
	std::stringstream stream;
	char buff[MAX_BUFF_SIZE];
	int next = 0;

	va_list args;
	va_start(args, msg);

	bool formatModifier = false; // true if the next char is for defining a var format
	while (*msg != '\0') {
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
				next += sprintf(&buff[next], "\nERROR: unrecognizable printf format specifier\n");
				break;
			}

			}
			formatModifier = false;
		}

		else {
			next += sprintf(&buff[next], "%c", *msg);
		}

		++msg;

		// Make sure we don't write past end of buffer
		if (next >= MAX_BUFF_SIZE-1)
			break;
	}
	sprintf(&buff[next], "\n");

	if (toConsole)
	{
		LogPrint(&buff[0]);
	}

	if (toFile)
	{
		LogFile(&buff[0]);
	}
}

inline void Logger::LogPrint(const char* msg) {
	std::cout << msg << std::endl;
}

inline void Logger::LogFile(const char* msg) {
	fprintf(fp, "%s", &msg[0]);
}