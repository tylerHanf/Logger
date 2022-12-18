#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string>

class Logger {
public:
	static void LogPrint(const char* msg, ...);
	static void LogFile(const char* msg, ...);
	static void InitLog(const char* logPath);

private:
	static void Log(const char* msg, bool toFile, va_list args);
};
