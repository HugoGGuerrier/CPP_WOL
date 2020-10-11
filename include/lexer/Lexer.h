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
     * The lexical result of the wanted file in a single array
     */
    std::vector<Token> lexResult;

    /**
     * Array that contains all expressions to stop the lecture head and optimize the lexical anlysis
     */
    const static char* stopString[];

    /**
     * All the stop string token codes to avoid searching in the lexical environment
     */
    const static int stopCodes[];

    // ----- Internal methods -----

    /**
     * Add a token with the wanted ID to the lex result
     *
     * @param tokenId The ID of the token to add
     */
    void addToken(int tokenId, int startPos, int endPos, int line, const char *value = nullptr);

public:

    // ----- Constructors -----

    /**
     * Construct a new lexer with the wanted file
     *
     * @param inputFile The pointer to the file you want to lex
     */
    explicit Lexer(const std::string &file);

    // ----- Getters -----

    /**
     * Get the lexing result in a vector by copying it
     *
     * @param result The vector you want to store the result in
     */
    void getLexResult(std::vector<Token> &result) const;

    // ----- Class methods -----

    /**
     * Do the lexical analysis process
     *
     * !!! Critical performance - use low level C functions !!!
     *
     * @throws FileException If the file is unreadable
     * @throws LexingException If the file contains unlexable tokens
     */
    void doLex();
};

#endif // CPP_WOL_LEXER_H
