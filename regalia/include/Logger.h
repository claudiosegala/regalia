#pragma once

class Logger {
public:
	static void Error(const std::string&, int type = 0);

	static void Info(const std::string&, int type = 0);

	static void Warning(const std::string&, int type = 0);
};