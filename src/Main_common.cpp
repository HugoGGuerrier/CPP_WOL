#include <string>
#include <iostream>
#include <cstring>

#include "Config.h"
#include "Logger.h"

#include "Main_common.h"

// ----- Class methods -----

void Main_common::displayHelp(bool full, bool dev) {
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
        helpText += "\t-log (-l) <log-file> : Write all logs in the specified file\n";
        helpText += "\t-memory (-m) <size> : Define the WOL memory size in MB (default 256 MB)\n";
        helpText += "\t-max-word-size (-mws) : Define the maximum identifier size in characters (default 128 char)\n";
        if(dev) {
            helpText += "\t-debug (-d) : Set the interpreter to the debug mode\n";
            helpText += "\t-color (-c) : Enable text color in the console (only on Linux for now)\n";
            helpText += "\t-test-mode (-tm) : Run all the unit tests and exit\n";
        }
    }

    helpText += "=====================================================";

    std::cout << helpText << std::endl;
}

void Main_common::readArgs(int argc, char *argv[], bool dev) {

    for(int i = 1; i < argc; i++) {
        char *currentArg = argv[i];

        // Test if the argument is an option
        if(Config::wolFile.empty() && currentArg[0] == '-') {

            // Test the option and set the configuration
            if(strcmp(currentArg, "-help") == 0 || strcmp(currentArg, "-h") == 0) {

                Config::helpFlag = true;

            } else if(strcmp(currentArg, "-include") == 0 || strcmp(currentArg, "-i") == 0) {

                char *tmpIncludes = argv[++i];
                char *include = strtok(tmpIncludes, ";");
                while(include != nullptr) {
                    Config::includePaths.emplace_back(include);
                    include = strtok(nullptr, ";");
                }

            } else if(strcmp(currentArg, "-log") == 0 || strcmp(currentArg, "-l") == 0) {

                Config::logFlag = true;
                Config::logFile = argv[++i];

            } else if(strcmp(currentArg, "-memory") == 0 || strcmp(currentArg, "-m") == 0) {

                try {
                    int size = std::stoi(argv[i + 1]);
                    if(size >= 1) {
                        Config::allocatedMemory = size;
                    } else {
                        Logger::log_warn("Cannot allocate less than 1 MB !");
                    }
                    i++;
                } catch (std::invalid_argument &e) {
                    Logger::log_warn("Cannot parse the provided memory size !");
                }

            } else if(strcmp(currentArg, "-max-word-size") == 0 || strcmp(currentArg, "-mws") == 0) {

                try {
                    int size = std::stoi(argv[i + 1]);
                    if(size >= 32) {
                        Config::maxWordSize = size;
                    } else {
                        Logger::log_warn("Cannot read identifier under 32 characters !");
                    }
                    i++;
                } catch (std::invalid_argument &e) {
                    Logger::log_warn("Cannot parse the provided max word size !");
                }

            } else if(strcmp(currentArg, "-debug") == 0 || strcmp(currentArg, "-d") == 0) {

                Config::debugFlag = true;

            } else if(strcmp(currentArg, "-color") == 0 || strcmp(currentArg, "-c") == 0) {

                Config::color = true;

            } else if(strcmp(currentArg, "-test-mode") == 0 || strcmp(currentArg, "-tm") == 0) {

                Config::testFlag = true;

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