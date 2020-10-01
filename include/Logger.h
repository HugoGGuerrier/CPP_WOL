#ifndef CPP_WOL_LOGGER_H
#define CPP_WOL_LOGGER_H

#include <iostream>

/**
 * This class is the WOL logger to display messages in the console and write it in the log if wanted
 */
class Logger {
private:

    // ----- Attributes -----

    inline const static int RED = 31;
    inline const static int GREEN = 32;
    inline const static int YELLOW = 33;
    inline const static int WHITE = 30;

    inline const static int RED_BG = 41;
    inline const static int GREEN_BG = 42;
    inline const static int YELLOW_BG = 43;

    // ----- Internal methods -----

    /**
     * Write a message in the console and the log file if the config say so
     *
     * @param msg The message to log
     */
    static void write_log(const std::string &msg, int fg = 0, int bg = 0);

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

    /**
     * Log a message durin a test
     *
     * @param msg The message to log
     */
    static void log_test_info(const std::string &msg);

    /**
     * Log a warning during a test
     *
     * @param msg The message to log
     */
    static void log_test_warn(const std::string &msg);

    /**
     * Log an error during a test
     *
     * @param msg The message to log
     */
    static void log_test_err(const std::string &msg);

    /**
     * Log a test success
     *
     * @param msg The message to log
     */
    static void log_test_success(const std::string &msg);

    /**
     * Log a test failure
     *
     * @param msg The message to log
     */
    static void log_test_failure(const std::string &msg);
};

#endif // CPP_WOL_LOGGER_H
