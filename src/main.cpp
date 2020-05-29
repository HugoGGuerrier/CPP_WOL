#include <iostream>

#include "Config.h"
#include "Logger.h"

/**
 * The function to display yhe console help
 */
void displayHelp(bool full) {
    std::string helpText;

    helpText += "====== cpp_owl : Native OWL interpreter (0.1a) ======\n";
    helpText += "Usage :\n";
    helpText += "\tcpp_owl [OPTIONS] <file-to-execute> [args...]\n\n";

    if(!full) {
        helpText += "Run \"cpp_owl -help\" for more information\n";
    } else {
        helpText += "Options :\n";
        helpText += "\t-help (-h) : Display this message\n";
        helpText += "\t-log (-l) <log-file> : Write all logs in the specified file\n";
        helpText += "\t-debug (-d) : Set the interpreter to the debug mode\n";
    }

    helpText += "=====================================================\n";

    std::cout << helpText << std::endl;
}


/**
 * This is the main entry point to the owl interpreter everything start from here
 *
 * @param argc The number of arguments
 * @param argv The arguments
 * @return If the interpreter runs without problems
 */
int main(int argc, char *argv[]) {
    // Test if the user provide correct number of arguments
    if(argc <= 1) {
        displayHelp(false);
        return 0;
    }

    // Read all arguments and parse them
    for(int i = 1; i < argc; i++) {
        std::string currentArg = argv[i];

        // Test if the argument is an option
        if(Config::owlFile.empty() && currentArg[0] == '-') {

            // Test the option and set the configuration
            if(currentArg == "-help" || currentArg == "-h") {
                Config::helpFlag = true;
            } else if(currentArg == "-log" || currentArg == "-l") {
                Config::logFlag = true;
                Config::logFile = argv[++i];
            } else if(currentArg == "-debug" || currentArg == "-d") {
                Config::debugFlag = true;
            }

        } else {

            // Set the OWL file or push the argument
            if(Config::owlFile.empty()) {
                Config::owlFile = currentArg;
            } else {
                Config::owlArgs.emplace_back(currentArg);
            }

        }
    }

    // Display the configuration
    if(Config::debugFlag) {
        Logger::log_dev("Interpreter configuration :\n" + Config::toString());
        Logger::log_dev("test");
    }

    // Display the help and quit if the flags is true
    if(Config::helpFlag) {
        displayHelp(true);
        return 0;
    }

    // Verify that the OWL file exists

    // Create and init the interpreter

    // Start the file interpretation

    // End of the OWL interpreter
    return 0;
}