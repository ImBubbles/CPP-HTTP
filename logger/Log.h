#pragma once
#include <string>
#include "LogLevel.h"

class Log {

	// CLASS VARS
public:

	static int LOG_LEVEL;
	static int LOG_FILTER;

	// CLASS METHODS
private:

	static std::string getLevelPrefix(int logLevel);

public:

	Log() = delete;

	static void log(int level, const std::string &message);
	static void debug(const std::string &message) {
		log(LogLevel::DEBUG, message);
	}
	static void info(const std::string &message) {
		log(LogLevel::INFO, message);
	}
	static void warning(const std::string &message) {
		log(LogLevel::WARNING, message);
	}
	static void error(const std::string &message) {
		log(LogLevel::ERROR, message);
	}

};
