#pragma once

#include <Util.h>

#include <iostream>
#include <string>

class Logger {
    public:

        ~Logger();

        static Logger* GetInstance();

        static void Error(const std::string&, int type = 0);

        static void Info(const std::string&, int type = 0);

        static void Warning(const std::string&, int type = 0);

    private:

        static Logger* instance;

        Logger();
};