#include <iostream>

#include "tools/Config.h"
#include "tools/Logger.h"
#include "tools/Utils.h"
#include "tests/TestEngine.h"
#include "exceptions/BootstrapException.h"

#include "Main_common.h"

/**
 * This is the main entry point to the WOL interpreter everything start from here
 *
 * @param argc The number of arguments
 * @param argv The arguments
 * @return If the interpreter runs without problems
 */
int main(int argc, char *argv[]) {
    // --- Initialize the application

    // Test if the user provide correct number of arguments
    if(argc <= 1) {
        Main_common::displayHelp(false, true);
        return 0;
    }

    // Parse arguments
    Main_common::readArgs(argc, argv, true);

    // Bootstrap the application
    try {
        Main_common::bootstrap();
    } catch (BootstrapException &e) {
        Logger::log_err(e.what());
    }

    // Display the configuration for the dev
    Logger::log_dev("Application initialization done !");
    Logger::log_dev("Interpreter configuration :\n" + Config::toString());

    // --- Run the application

    // Display the help and quit if the flags is true
    if(Config::helpFlag) {
        Main_common::displayHelp(true, true);
        return 0;
    }

    // Execute the tests if the flag is true
    if(Config::testFlag) {
        return TestEngine::run();
    }

    // Create and init the interpreter

    // Start the file interpretation

    // End of the WOL interpreter
    return 0;
}