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
     * Process a string following the lexical environment and create the token if one is found
     *
     * @param stringToProcess The string to process
     * @param resultToken The token to store the result of processing
     * @return The id of the found token, -1 else
     */
    [[nodiscard]] int processString(const std::string &stringToProcess) const;

    /**
     * Add a token with the wanted ID to the lex result
     *
     * @param tokenId The ID of the token to add
     */
    void addToken(int tokenId, int startPos, int endPos, int line);

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
     * @throws FileException If the file is unreadable
     * @throws LexingException If the file contains unlexable tokens
     */
    void doLex();
};

#endif // CPP_WOL_LEXER_H
