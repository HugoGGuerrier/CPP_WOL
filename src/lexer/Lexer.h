#ifndef CPP_WOL_LEXER_H
#define CPP_WOL_LEXER_H

#include <fstream>
#include <vector>
#include "Token.h"

class Lexer {
private:

    // ----- Attributes -----

    /**
     * The file to lex
     */
    std::ifstream *inputFile;

    /**
     * The lexical result of the wanted file
     */
    std::vector<Token> *lexResult;

    // ----- Internal methods -----



public:

    // ----- Constructors -----

    /**
     * Construct a new lexer with the wanted file
     *
     * @param inputFile The pointer to the file you want to lex
     */
    explicit Lexer(std::ifstream *inputFile);

    // ----- Getters -----

    std::vector<Token> &getLexResult();

    // ----- Class methods -----

    /**
     * Start the lexing
     *
     * @return 0 if the lexing worked, 1 else
     */
    int doLex();

};

#endif // CPP_WOL_LEXER_H
