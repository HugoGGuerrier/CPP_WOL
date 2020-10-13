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

    // --- Instance

    /**
     * The absolute path of the file to lex
     */
    std::string file;

    /**
     * The lexical result of the wanted file in a single array
     */
    std::vector<Token> lexResult;

    // --- Static

    /**
     * Array that contains all expressions to stop the lecture head and optimize the lexical anlysis
     */
    const static char stopChars[];

    /**
     * All the stop string token codes to avoid searching in the lexical environment
     */
    const static int stopCodes[];

    /**
     * The number of stop characters
     */
    inline const static int stopCharsNumber = 22;

    /**
     * Normal state of the lexer
     */
    inline const static int NORMAL_STATE = 0;

    /**
     * When you encounter a one line comment
     */
    inline const static int ONE_LINE_COMMENT_STATE = 1;

    /**
     * When you encounter a multi line comment
     */
    inline const static int MULTI_LINE_COMMENT_STATE = 2;

    // ----- Internal methods -----

    /**
     * Test if a char is a stop character in the lexical analysis
     *
     * @param charToTest The char to test
     * @return The character code to simplify lexical analysis, -1 if it's not
     */
    static int getStopCharCode(char charToTest);

    /**
     * Test if a string is in the lexical environment
     *
     * @param strToTest The string to test
     * @return The lexical token code, -1 if not in the lexical environment
     */
    static int getLexicalTokenCode(char *strToTest);

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
