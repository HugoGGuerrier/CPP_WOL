#ifndef CPP_WOL_PROGRAMS_H
#define CPP_WOL_PROGRAMS_H

#include "parser/ast/Program.h"

#include <string>
#include <unordered_map>

/**
 * This static class contains all parsed files Program
 */
class Programs {
private:

    // ----- Attributes -----

    /**
     * The map of the parsed file with the SHA-256 file directory hash as key
     */
    static std::unordered_map<std::string, Program &> parsedFiles;

public:

    // ----- Getters -----

    static const Program & getProgramFromFile(std::string file);

    // ----- Setters -----

    static void addProgram(const std::string & filePath, const Program & program);

};


#endif //CPP_WOL_PROGRAMS_H
