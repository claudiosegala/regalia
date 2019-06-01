#pragma once

class Logger {
public:
	static void Error(const std::string& msg, int type = 0);

	static void Info(const std::string& msg, int type = 0);

	static void Warning(const std::string& msg, int type = 0);
};