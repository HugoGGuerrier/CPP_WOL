#include "Config.h"
#include "Utils.h"

// ----- Static attributes init -----

bool Config::helpFlag = false;
bool Config::debugFlag = false;
bool Config::logFlag = false;
std::string Config::logFile = std::string();
std::string Config::owlFile = std::string();
std::vector<std::string> Config::owlArgs = std::vector<std::string>();

// ----- Class method -----

std::string Config::toString() {
    std::string res;

    res += "\thelpFlag = " + btos(Config::helpFlag) + "\n";
    res += "\tdebugFlag = " + btos(Config::debugFlag) + "\n";
    res += "\tlogFlag = " + btos(Config::logFlag) + "\n";
    res += "\tlogFile = " + Config::logFile + "\n";
    res += "\towlFile = " + Config::owlFile + "\n";

    std::string owlArgsString = "\towlArgs = <";
    for(std::string const &owlArg : Config::owlArgs) {
        owlArgsString += owlArg + " ";
    }
    res += owlArgsString + ">" + "";

    return res;
}
