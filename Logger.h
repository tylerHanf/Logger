#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string>

enum LogDest
{
	DEST_FILE = 0x1,
	DEST_CONSOLE = 0x2,
};

enum LogLevel
{
	SEV_INFO = 0x1,
	SEV_WARN = 0x2,
	SEV_CRITICAL = 0x4
};

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__) || defined(WIN64) || defined(_WIN64) || defined(__NT__)
#define FILE_SEP '\\'
#else
#define FILE_SEP '/'
#endif

#define __FILENAME__ (strrchr(__FILE__, FILE_SEP) ? strrchr(__FILE__, FILE_SEP) + 1 : __FILE__)

// Assume we always want to log critical
#ifndef NO_LOG
#define LOG_CRITICAL(msg, ...)(Logger::Log("CRITICAL", __FILENAME__, __func__, __LINE__, SEV_CRITICAL, msg, __VA_ARGS__))
#define DEFAULT_SEV SEV_CRITICAL
#define LOG_INFO
#define LOG_WARN
#endif

// Allow additional debug if desired
#ifdef _DEBUG
	#define DEFAULT_SEV (SEV_INFO | SEV_WARN | SEV_CRITICAL)
	#define LOG_INFO(msg, ...)(Logger::Log("INFO", __FILENAME__, __func__, __LINE__, SEV_INFO, msg, __VA_ARGS__)) 
	#define LOG_WARN(msg, ...)(Logger::Log("WARN", __FILENAME__, __func__, __LINE__, SEV_WARN, msg, __VA_ARGS__))
#endif

class Logger {
public:

	static void Log(const std::string& sev_msg, const std::string& filename, const std::string& funcName, int lineNum, LogLevel level, const char* msg, ...);
	static void InitLog(const char* logPath, LogLevel level=SEV_INFO, int destFlags=DEST_CONSOLE);
	static void SetLogDest(int destFlag);
	static void SetLogLevel(uint32_t level);

private:
	static void LogPrint(const char* msg, LogLevel level);
	static void LogFile(const char* msg);
};
