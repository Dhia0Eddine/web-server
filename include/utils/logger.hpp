// I provide corrected code like this:
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>  // Added missing include

namespace HDE {

class Logger {
public:
    enum Level { INFO, WARNING, ERROR, DEBUG };

    static void log(const std::string& message, Level level = INFO) {
        const char* levelStr;
        const char* colorCode;

        switch (level) {
            case INFO: levelStr = "INFO"; colorCode = "\033[32m"; break;
            case WARNING: levelStr = "WARN"; colorCode = "\033[33m"; break;
            case ERROR: levelStr = "ERROR"; colorCode = "\033[31m"; break;
            case DEBUG: levelStr = "DEBUG"; colorCode = "\033[34m"; break;
        }

        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        
        // Fixed: Remove newline from ctime() output
        std::string time_str = std::ctime(&now_time);
        time_str.pop_back(); // Remove trailing \n

        std::cout << colorCode << "[" << time_str
                  << "] [" << levelStr << "] " << message << "\033[0m" << std::endl;
    }
};

}

#endif // LOGGER_HPP

// 