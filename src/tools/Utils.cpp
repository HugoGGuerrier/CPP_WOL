#include <cstdlib>
#include <memory>

#include "tools/Utils.h"

std::string btos(const bool b) {
    return b ? "true" : "false";
}

bool fileExists(const std::string &file) {
    FILE *fileToTest = nullptr;
    fileToTest = fopen(file.c_str(), "r");
    return fileToTest != nullptr;
}

// ----- Vector displaying functions -----

std::string vectos(const std::vector<std::string> &vector, bool newLine) {
    std::string res = "<";

    if(newLine) res.append("\n");
    for(int i = 0; i < vector.size(); i++) {
        res.append(vector[i]);
        if(i < vector.size() - 1) {
            res.append(newLine ? "\n": ", ");
        }
    }
    if(newLine) res.append("\n");
    res.append(">");

    return res;
}