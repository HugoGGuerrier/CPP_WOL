#ifndef CPP_OWL_LOGGER_H
#define CPP_OWL_LOGGER_H

#include <iostream>

/**
 * This class is the OWL logger to display messages in the console and write it in the log if wanted
 */
class Logger {
private:

    /**
     * Write a message in the console and the log file if the config say so
     *
     * @param msg The message to log
     */
    static void write_log(const std::string &msg);

public:

    /**
     * Log a development information
     *
     * @param msg The message to log
     */
    static void log_dev(const std::string &msg);

    /**
     * Log a warning information
     *
     * @param msg The message to log
     */
    static void log_warn(const std::string &msg);

    /**
     * Log an error
     *
     * @param msg The message to log
     */
    static void log_err(const std::string &msg);
};

#endif
