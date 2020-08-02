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

    static bool helpFlag;
    static bool debugFlag;
    static bool logFlag;
    static std::string logFile;
    static std::string wolFile;
    static std::vector<std::string> wolArgs;
    static std::vector<std::string> includePaths;

    // ----- Class methods -----

    /**
     * Get a string representing the interpreter configuration
     *
     * @return The configuration
     */
    static std::string toString();
};

#endif // CPP_WOL_CONFIG_H