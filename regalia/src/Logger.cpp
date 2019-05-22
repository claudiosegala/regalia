#include <Logger.h>

Logger* Logger::instance;

Logger::Logger() {
    if (this->instance != nullptr) {
        throw std::runtime_error("There should be only one instance!\n");
    }

    this->instance = this;
}

Logger::~Logger() {}

Logger* Logger::GetInstance () {
    if (Logger::instance != nullptr) {
        return Logger::instance;
    }
    
    return Logger::instance = new Logger();
}

void Logger::Error(const std::string &msg, int type) {
    #ifdef LOG_ERROR
        std::cout << Constants::StdColor::Red << "\n";
        if (type == 0 || type == 2) {
            std::cout << "> [error]: ";    
        }

        std::cout << msg;

        if (type == 0 || type == 1) {
            std::cout << "\n\n";
        }
        std::cout << Constants::StdColor::Reset;
    #else
        // Avoid warnings
        (void)msg;
        (void)type;
    #endif
}

void Logger::Info(const std::string &msg, int type) {
    #ifdef LOG_INFO
        if (type == 0 || type == 2) {
            std::cout << "> [info]: ";    
        }

        std::cout << msg;

        if (type == 0 || type == 1) {
            std::cout << "\n";
        }
    #else
        // Avoid warnings
        (void)msg;
        (void)type;
    #endif
}

void Logger::Warning(const std::string &msg, int type) {
    #ifdef LOG_WARN
        std::cout << Constants::StdColor::Yellow;
        if (type == 0 || type == 2) {
            std::cout << "> [warn]: ";    
        }

        std::cout << msg;

        if (type == 0 || type == 1) {
            std::cout << "\n";
        }
        std::cout << Constants::StdColor::Reset;
    #else
        // Avoid warnings
        (void)msg;
        (void)type;
    #endif
}
