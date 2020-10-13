#include <iostream>

#include "Main_common.h"
#include "Config.h"
#include "Logger.h"
#include "Utils.h"

/**
 * This is the main entry point to the WOL interpreter everything start from here
 *
 * @param argc The number of arguments
 * @param argv The arguments
 * @return If the interpreter runs without problems
 */
int main(int argc, char *argv[]) {
    // Test if the user provide correct number of arguments
    if(argc <= 1) {
        Main_common::displayHelp(false, false);
        return 0;
    }

    // Parse arguments
    Main_common::readArgs(argc, argv, false);

    Logger::log_dev("Interpreter configuration :\n" + Config::toString());

    // Display the help and quit if the flags is true
    if(Config::helpFlag) {
        Main_common::displayHelp(true, false);
        return 0;
    }

    // Verify that the WOL file exists
    if(!fileExists(Config::wolFile)) {
        std::cout << "Specified WOL file " << Config::wolFile << " is missing or unreadable" << std::endl;
        return 1;
    }

    // Create and init the interpreter

    // Start the file interpretation

    // End of the WOL interpreter
    return 0;
}