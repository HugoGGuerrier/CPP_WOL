#ifndef CPP_WOL_FILEPOOL_H
#define CPP_WOL_FILEPOOL_H

#include <unordered_map>
#include <string>

#include "parser/ast/Program.h"

/**
 * This class contains all imported files and their AST to avoid importing multiple imports
 */
class FilePool {
private:

    /**
     * The map that associate files with their programs
     */
    static std::unordered_map<std::string, Program>;

public:
};


#endif // CPP_WOL_FILEPOOL_H
