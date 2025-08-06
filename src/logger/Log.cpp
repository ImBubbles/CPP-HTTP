#include <iostream>
#include "Log.h"

namespace ANSI {
	const std::string RESET = "\033[0m";
	const std::string RED = "\033[31m";
	const std::string GREEN = "\033[32m";
	const std::string YELLOW = "\033[33m";
	const std::string BLUE = "\033[34m";
	const std::string MAGENTA = "\033[35m";
	const std::string CYAN = "\033[36m";
	const std::string WHITE = "\033[37m";

	// You can also add bold, background colors, etc.
	const std::string BOLD = "\033[1m";
}

std::string Log::getLevelPrefix(const int logLevel) {
	switch (logLevel) {
		case DEBUG:
			return ANSI::CYAN + "[DEBUG]";
		case WARNING:
			return ANSI::YELLOW + "[WARNING]";
		case ERROR:
			return ANSI::RED + "[ERROR]";
		default:
			return ANSI::RESET + "[INFO]";

	}
}

void Log::log(const int level, const std::string &message) {
	if (level < Log::LOG_FILTER)
		return;
	std::cout << getLevelPrefix(level) + " " + message << ANSI::RESET << std::endl;
}

int Log::LOG_FILTER = 0;
int Log::LOG_LEVEL = 0;