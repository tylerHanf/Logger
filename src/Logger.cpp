#include "Logger.h"
#include <iostream>

static const char* logPath;
static std::FILE* fp;

void Logger::LogPrint(const char* msg, ...) {
	va_list args;
	va_start(args, msg);
	Logger::Log(msg, false, args);
}

void Logger::LogFile(const char* msg, ...) {
	va_list args;
	va_start(args, msg);
	Logger::Log(msg, true, args);
}

void Logger::InitLog(const char* logPath) {
	fopen_s(&fp, logPath, "w");
	if (fp != NULL) {
		printf("Initialized Logger\n");
	}

	else {
		printf("ERROR: Failed to initialize Logger\n");
	}
}

/*
* Main logic for handling logging args
* Format specifiers:
*		-d = int
*       -f = double
*       -c = char
*       -s = string
*/
void Logger::Log(const char* msg, bool toFile, va_list args) {

	std::FILE* o_stream = toFile ? fp : stdout;

	bool formatModifier = false; // true if the next char is for defining a var format
	while (*msg != '\0') {
		if (*msg == '%') { formatModifier = true; }

		else if (formatModifier) {

			switch (*msg) {
			case 'd':
			{
				int i = va_arg(args, int);
				fprintf(o_stream, "%d", i);
				break;
			}

			case 'f':
			{
				double f = va_arg(args, double);
				fprintf(o_stream, "%f", f);
				break;
			}

			case 'c':
			{
				int c = va_arg(args, int);
				fprintf(o_stream, "%c", c);
				break;
			}

			case 's':
			{
				char* s = va_arg(args, char*);
				fprintf(o_stream, "%s", s);
				break;
			}

			default:
			{
				fprintf(o_stream, "\nERROR: unrecognizable printf format specifier\n");
				break;
			}

			}
			formatModifier = false;
		}

		else {
			fprintf(o_stream, "%c", *msg);
		}

		++msg;
	}
	fprintf(o_stream, "\n");
}
