#include "Config.h"
#include "Utils.h"

// ----- Class method -----

std::string Config::toString() {
    std::string res;

    res += "\tversion = " + Config::version + "\n";

    res += "\thelpFlag = " + btos(Config::helpFlag) + "\n";
    res += "\tdebugFlag = " + btos(Config::debugFlag) + "\n";
    res += "\tlogFlag = " + btos(Config::logFlag) + "\n";
    res += "\tlogFile = " + Config::logFile + "\n";
    res += "\twolFile = " + Config::wolFile + "\n";

    std::string wolArgsString = "\twolArgs = <";
    for(std::string const &wolArg : Config::wolArgs) {
        wolArgsString += wolArg + " ";
    }
    res += wolArgsString + ">" + "\n";

    std::string includePathsString = "\tincludePaths = <";
    for(std::string const &includePath : Config::includePaths) {
        includePathsString += includePath + " ";
    }
    res += includePathsString + ">" + "\n";

    res += "\twolSize = " + std::to_string(Config::wolSize) + "";

    return res;
}