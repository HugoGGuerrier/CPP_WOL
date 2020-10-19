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

int getEscapedChar(char charToEscape) {
    switch (charToEscape) {
        case '0':
            return '\0';

        case 'n':
            return '\n';

        case 'r':
            return '\r';

        case 't':
            return '\t';

        case '"':
            return '\"';

        case '\'':
            return '\'';

        case '\\':
            return '\\';

        case 'b':
            return '\b';

        default:
            return -1;
    }
}