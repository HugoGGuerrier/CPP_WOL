#include <fstream>

#include "Logger.h"
#include "Config.h"

void Logger::write_log(const std::string &msg, int fg, int bg) {
    // Init the result string;
    std::string finalMessage = msg;

    // Create the colored message
    if(Config::color) {
        std::string coloredString;
        if(fg != 0 || bg != 0) {

            coloredString.append(msg);
            coloredString.append("\033[0m");
        }

        msg = coloredString;
    }

    // Write in the console
    std::cout << finalMessage << std::endl;

    // Write in the log file
    if(Config::logFlag && !Config::logFile.empty()) {
        std::ofstream logFile;
        logFile.open(Config::logFile, std::ios::out | std::ios::app);
        logFile << msg << std::endl;
        logFile.close();
    }
}

void Logger::log_dev(const std::string &msg) {
    if(Config::debugFlag) {
        Logger::write_log("[INFO] " + msg);
    }
}

void Logger::log_warn(const std::string &msg) {
    Logger::write_log("[WARNING] " + msg, Logger::YELLOW);
}

void Logger::log_err(const std::string &msg) {
    Logger::write_log("[ERROR] " + msg, Logger::RED);
}

void Logger::log_test_info(const std::string &msg) {
    if(Config::testFlag) {
        Logger::write_log("[TEST - INFO] " + msg, Logger::GREEN);
    }
}

void Logger::log_test_warn(const std::string &msg) {
    if(Config::testFlag) {
        Logger::write_log("[TEST - WARNING] " + msg, Logger::YELLOW);
    }
}

void Logger::log_test_err(const std::string &msg) {
    if(Config::testFlag) {
        Logger::write_log("[TEST - ERROR] " + msg, Logger::RED);
    }
}
