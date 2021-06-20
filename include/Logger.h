#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string>

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat3.h"
#include "Mat4.h"
#include "Quaternion.h"

class Logger {
public:
	static void LogPrint(const char* msg, ...);

	// Print Matrix/Vectors/Quaternions
	// Could add variadic features for printing attributes of math objects

	static void LogFile(const char* msg, ...);
	static void InitLog(const char* logPath);

private:
	static void Log(const char* msg, bool toFile, va_list args);
	static void Log_Vec2(const Vec2& vec, std::FILE* o_stream);
	static void Log_Vec3(const Vec3& vec, std::FILE* o_stream);
	static void Log_Vec4(const Vec4& vec, std::FILE* o_stream);
	static void Log_Mat3(const Mat3& mat, std::FILE* o_stream);
	static void Log_Mat4(const Mat4& mat, std::FILE* o_stream);
	static void Log_Quat(const Quaternion& quat, std::FILE* o_stream);
};
