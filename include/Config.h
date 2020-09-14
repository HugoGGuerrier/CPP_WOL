#ifndef CPP_WOL_CONFIG_H
#define CPP_WOL_CONFIG_H

#include <iostream>
#include <vector>

/**
 * This class contains all static attributes of the interpreter configuration
 */
class Config {
public:

    // ----- Attributes -----

    inline const static std::string version = "0.1a";

    inline static bool helpFlag = false;
    inline static bool debugFlag = false;
    inline static bool logFlag = false;
    inline static bool testFlag = false;
    inline static std::string logFile = std::string();
    inline static std::string wolFile = std::string();
    inline static std::vector<std::string> wolArgs = std::vector<std::string>();
    inline static std::vector<std::string> includePaths = std::vector<std::string>();
    inline static int wolSize = 256;

    // ----- Class methods -----

    /**
     * Get a string representing the interpreter configuration
     *
     * @return The configuration
     */
    static std::string toString();
};

#endif // CPP_WOL_CONFIG_H