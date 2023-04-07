#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string>

enum LogDest
{
	DEST_FILE = 0x1,
	DEST_CONSOLE = 0x2,
};

class Logger {
public:
	static void Log(const char* msg, ...);
	static void InitLog(const char* logPath, int destFlags=DEST_CONSOLE);
	static void SetLogDest(int destFlag);

private:
	static void LogPrint(const char* msg);
	static void LogFile(const char* msg);
};
