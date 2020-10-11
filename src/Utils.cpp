#include <fstream>
#include <memory>

#include "Utils.h"

std::string btos(const bool b) {
    return b ? "true" : "false";
}

bool fileExists(const std::string &file) {
    std::unique_ptr<std::ifstream> fileStream = std::make_unique<std::ifstream>(std::ifstream(file));
    if(!file.empty()) {
        fileStream->open(file);
        if(fileStream->is_open()) {
            fileStream->close();
            return true;
        }
    }
    return false;
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