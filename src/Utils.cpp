#include <fstream>

#include "Utils.h"

/**
 * Function to convert a boolean to its string representation
 *
 * @param b The boolean to convert
 * @return The boolean string representation
 */
std::string btos(const bool b) {
    return b ? "true" : "false";
}

/**
 * Function to test if a file exists
 *
 * @param file The file name to tests
 * @return True if the file exists
 */
bool fileExists(const std::string &file) {
    std::ifstream fileStream;
    if(!file.empty()) {
        fileStream.open(file);
        if(fileStream.is_open()) {
            fileStream.close();
            return true;
        }
    }
    return false;
}