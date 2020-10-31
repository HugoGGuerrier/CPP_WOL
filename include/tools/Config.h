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

    inline const static std::string version = "0.2a";
    inline const static std::string basePath = "/home/hugo/Projects/desktop/CPP_WOL";

    inline static bool color = false;
    inline static bool helpFlag = false;
    inline static bool debugFlag = false;
    inline static bool logFlag = false;
    inline static bool testFlag = false;
    inline static bool lazyLexer = false;
    inline static std::string logFile = std::string();
    inline static std::string wolFile = std::string();
    inline static std::vector<char *> wolArgs = std::vector<char *>();
    inline static std::vector<char *> includePaths = std::vector<char *>();
    inline static int allocatedMemory = 256;
    inline static int maxWordSize = 128;

    // ----- Class methods -----

    /**
     * Get a string representing the interpreter configuration
     *
     * @return The configuration
     */
    static std::string toString();
};

#endif // CPP_WOL_CONFIG_H
