#include <fstream>

#include "Logger.h"
#include "Config.h"

void Logger::write_log(const std::string &msg) {
    // Write in the console
    std::cout << msg << std::endl;

    // Write in the log file
    if(Config::logFlag && !Config::logFile.empty()) {
        std::ofstream logFile;
        logFile.open(Config::logFile, std::ios::out | std::ios::app);
        logFile << msg << std::endl;
        logFile.close();
    }
}

void Logger::log_dev(const std::string &msg) {
    Logger::write_log("[INFO] " + msg);
}

void Logger::log_warn(const std::string &msg) {
    Logger::write_log("[WARNING] " + msg);
}

void Logger::log_err(const std::string &msg) {
    Logger::write_log("[ERROR] " + msg);
}
