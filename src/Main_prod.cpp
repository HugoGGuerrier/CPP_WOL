#include <iostream>
#include <fstream>
#include <cstring>

#include "Config.h"
#include "Logger.h"
#include "Utils.h"

/**
 * The function to display the console help
 */
void displayHelp(bool full) {
    std::string helpText;

    helpText += "====== cpp_wol : Native WOL interpreter (" + Config::version + ") ======\n";
    helpText += "Usage :\n";
    helpText += "\tcpp_wol [OPTIONS] <file-to-execute> [args...]\n\n";

    if(!full) {
        helpText += "Run \"cpp_wol -help\" for more information\n";
    } else {
        helpText += "Options :\n";
        helpText += "\t-help (-h) : Display this message\n";
        helpText += "\t-include (-i) : A list of directory to look sources in separated by \";\"\n";
        helpText += "\t-memory (-m) <size> : Define the WOL heap size in MB\n";
        helpText += "\t-log (-l) <log-file> : Write all logs in the specified file\n";
    }

    helpText += "=====================================================";

    std::cout << helpText << std::endl;
}

/**
 * This function is to read the arguments and parse them
 *
 * @param argc The number of arguments
 * @param argv The list of arguments
 */
void readArgs(int argc, char *argv[]) {

    for(int i = 1; i < argc; i++) {
        std::string currentArg = argv[i];

        // Test if the argument is an option
        if(Config::wolFile.empty() && currentArg[0] == '-') {

            // Test the option and set the configuration
            if(currentArg == "-help" || currentArg == "-h") {

                Config::helpFlag = true;

            } else if(currentArg == "-log" || currentArg == "-l") {

                Config::logFlag = true;
                Config::logFile = argv[++i];

            } else if(currentArg == "-include" || currentArg == "-i") {

                char *tmpIncludes = argv[++i];
                char *include = strtok(tmpIncludes, ";");
                while(include != nullptr) {
                    Config::includePaths.emplace_back(include);
                    include = strtok(nullptr, ";");
                }

            }

        } else {

            // Set the WOL file or push the argument
            if(Config::wolFile.empty()) {
                Config::wolFile = currentArg;
            } else {
                Config::wolArgs.emplace_back(currentArg);
            }

        }
    }

}

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
        displayHelp(false);
        return 0;
    }

    // Parse arguments
    readArgs(argc, argv);

    // Display the configuration
    if(Config::debugFlag) {
        Logger::log_dev("VirtualMachine configuration :\n" + Config::toString());
    }

    // Display the help and quit if the flags is true
    if(Config::helpFlag) {
        displayHelp(true);
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