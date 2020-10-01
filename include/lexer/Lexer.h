#ifndef CPP_WOL_LEXER_H
#define CPP_WOL_LEXER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>

#include "Token.h"

class Lexer {
private:

    // ----- Attributes -----

    /**
     * The absolute path of the file to lex
     */
    std::string file;

    /**
     * The lexical result of the wanted file
     */
    std::vector<Token> lexResult;

    // ----- Internal methods -----

    /**
     * Process a string following the lexical environment
     *
     * @param stringToProcess The string to process
     * @param resultToken The token to store the result of processing
     * @throws LexingException if the string have a lexing exception
     */
    void processString(const std::string &stringToProcess, Token &resultToken) const;

public:

    // ----- Constructors -----

    /**
     * Construct a new lexer with the wanted file
     *
     * @param inputFile The pointer to the file you want to lex
     */
    explicit Lexer(const std::string &file);

    // ----- Getters -----

    void getLexResult(std::vector<Token> &result) const;

    // ----- Class methods -----

    /**
     * Start the lexing
     *
     * @return 0 if the lexing worked, 1 else
     */
    void doLex();
};

#endif // CPP_WOL_LEXER_H
