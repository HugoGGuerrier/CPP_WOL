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