#include <fstream>

#include "tools/Logger.h"
#include "tools/Config.h"

void Logger::write_log(const std::string &msg, int fg, int bg) {
    // Init the result string;
    std::string finalMessage;

    if(Config::color) {

        // Create the colored message
        if(fg != 0 || bg != 0) {
            finalMessage.append("\033[");
            if(fg != 0) finalMessage.append(std::to_string(fg));
            if(fg != 0 && bg != 0) finalMessage.append(";");
            if(bg != 0) finalMessage.append(std::to_string(bg));
            finalMessage.append("m");
        }

        finalMessage.append(msg);
        finalMessage.append("\033[0m");

    } else {

        // Just add the message without color
        finalMessage.append(msg);

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

void Logger::log_test_success(const std::string &msg) {
    if(Config::testFlag) {
        Logger::write_log("[TEST - SUCCESS] " + msg, Logger::WHITE, Logger::GREEN_BG);
    }
}

void Logger::log_test_failure(const std::string &msg) {
    if(Config::testFlag) {
        Logger::write_log("[TEST - FAILURE] " + msg, Logger::WHITE, Logger::RED_BG);
    }
}
