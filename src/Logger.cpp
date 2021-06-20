#include "Logger.h"

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
*       -2 = Vec2
*       -3 = Vec3
*       -4 = Vec4
*       -m = Mat3
*       -M = Mat4
*       -q = Quaternion
*/
void Logger::Log(const char* msg, bool toFile, va_list args) {

	std::FILE* o_stream = toFile ? fp : stdout;

	bool formatModifier = false; // true if the next char is for defining a var format
	while (*msg != '\0') {
		if (*msg == '%') { formatModifier = true; }

		else if (formatModifier) {

			if (*msg == 'd') {
				int i = va_arg(args, int);
				fprintf(o_stream, "%d", i);
			}

			else if (*msg == 'f') {
				double f = va_arg(args, double);
				fprintf(o_stream, "%f", f);
			}

			else if (*msg == 'c') {
				int c = va_arg(args, int);
				fprintf(o_stream, "%c", c);
			}

			else if (*msg == '2') {
				Vec2 vec = va_arg(args, Vec2);
				Log_Vec2(vec, o_stream);
			}

			else if (*msg == '3') {
				Vec3 vec = va_arg(args, Vec3);
				Log_Vec3(vec, o_stream);
			}

			else if (*msg == '4') {
				Vec4 vec = va_arg(args, Vec4);
				Log_Vec4(vec, o_stream);
			}

			else if (*msg == 'm') {
				Mat3 mat = va_arg(args, Mat3);
				Log_Mat3(mat, o_stream);
			}

			else if (*msg == 'M') {
				Mat4 mat = va_arg(args, Mat4);
				Log_Mat4(mat, o_stream);
			}

			else if (*msg == 'q') {
				Quaternion q = va_arg(args, Quaternion);
				Log_Quat(q, o_stream);
			}

			else {
				fprintf(o_stream, "\nERROR: unrecognizable printf format specifier\n");
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

void Logger::Log_Vec2(const Vec2& vec, std::FILE* o_stream) {
	fprintf(o_stream, "[ %f, %f ]\n", vec[0], vec[1]);
}

void Logger::Log_Vec3(const Vec3& vec, std::FILE* o_stream) {
	fprintf(o_stream, "[ %f, %f, %f ]\n", vec[0], vec[1], vec[2]);
}

void Logger::Log_Vec4(const Vec4& vec, std::FILE* o_stream) {
	fprintf(o_stream, "[ %f, %f, %f, %f ]\n", vec[0], vec[1], vec[2], vec[3]);
}

void Logger::Log_Mat3(const Mat3& mat, std::FILE* o_stream) {
	fprintf(o_stream, "[ %f, %f, %f\n", mat[0][0], mat[0][1], mat[0][2]);
	fprintf(o_stream, "  %f, %f, %f\n", mat[1][0], mat[1][1], mat[1][2]);
	fprintf(o_stream, "  %f, %f, %f ]\n", mat[2][0], mat[2][1], mat[2][2]);
}

void Logger::Log_Mat4(const Mat4& mat, std::FILE* o_stream) {
	fprintf(o_stream, "[ %f, %f, %f\n", mat[0][0], mat[0][1], mat[0][2]);
	fprintf(o_stream, "  %f, %f, %f\n", mat[1][0], mat[1][1], mat[1][2]);
	fprintf(o_stream, "  %f, %f, %f\n", mat[2][0], mat[2][1], mat[2][2]);
	fprintf(o_stream, "  %f, %f, %f ]\n", mat[3][0], mat[3][1], mat[3][2]);
}

void Logger::Log_Quat(const Quaternion& quat, std::FILE* o_stream) {
	fprintf(o_stream, "R: %f, I: [ %f, %f, %f ]\n", quat.r, quat.i[0], quat.i[1], quat.i[2]);
}

