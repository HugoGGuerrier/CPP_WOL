#ifndef CPP_WOL_LEXER_H
#define CPP_WOL_LEXER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>

#include "Token.h"

/**
 * The lexer data structure to avoid storing it in the class
 */
struct lexer_data {
    /** The lexical buffer */
    char *buffer = nullptr;
    unsigned int bufferPointer = 0;

    /** The current lexer state */
    int currentState = -1;

    /** Current pos and line to store the position in the file to lex */
    unsigned int currentPos = 1;
    unsigned int currentLine = 1;

    /** Lexical analysis flags, to help pass from a state to another */
    bool WINDOWS_NEW_LINE_FLAG = false;
    bool COMMENT_START_FLAG = false;
    bool COMMENT_MULTILINE_END_FLAG = false;
};

/**
 * This class contain a lexer attached to a file and the result of the lexical analysis on this file
 */
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

    /**
     * When you encounter a string
     */
    inline const static int STRING_STATE = 3;

    // ----- Internal methods -----

    /**
     * Evaluate a char with the normal state actions
     *
     * @param charToEval The char to eval
     * @param data The lexer data
     */
    void evalChar(char charToEval, lexer_data *data);

    /**
     * Update the position in the file to lex to keep the correct position in the data
     *
     * @param charToEval The char to eval
     * @param data The lexer data
     */
    void updatePosition(char charToEval, lexer_data *data);

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
