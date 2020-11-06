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
    /** The file */
    FILE *file;

    /** The lexical buffer */
    char *buffer = nullptr;
    unsigned int bufferPointer = 0;

    /** The current lexer state */
    int currentState = -1;

    /** Current pos and line to store the position in the file to lex */
    unsigned int currentPos = 1;
    unsigned int currentLine = 1;

    /** Buffer for string values */
    std::string stringValueBuffer;

    /** Error handling vars */
    unsigned int errorLine = 1;
    unsigned int errorPos = 1;
    std::string errorMessage;
};

/**
 * This structure contains all lexer flags
 */
struct lexer_flags {
    bool ERROR_FLAG = false;
    bool WINDOWS_NEW_LINE_FLAG = false;
    bool COMMENT_START_FLAG = false;
    bool COMMENT_MULTILINE_END_FLAG = false;
    bool NEXT_ESCAPED_FLAG = false;
    bool LEXING_DONE = false;
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

    /**
     * The pointer to return token in order
     */
    unsigned long resultPointer;

    /**
     * Data of the lexer to process the lexical analysis
     */
    lexer_data lexerData;

    /**
     * Flags of the lexer to process the lexical analysis
     */
    lexer_flags lexerFlags;

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
     * Evaluate the current buffer and append it to the lexing result
     */
    void doBufferLexing();

    /**
     * Update the position in the file to lex to keep the correct position in the data
     *
     * @param charToEval The char to eval
     */
    void updatePosition(char charToEval);

    /**
     * Raise an error at the wanted line and with the wanted message, use it to uniform error raising in the Lexer
     *
     * @param message The message to display
     * @param line The line of the error
     * @param pos The position of the error
     */
    void raiseError(const std::string &message, unsigned int line, unsigned int pos);

    /**
     * Add a token with the wanted ID to the lex result
     *
     * @param tokenId The ID of the token to add
     */
    void addToken(int tokenId, unsigned int startPos, unsigned int endPos, unsigned int line, const char *value = nullptr, unsigned int size = 0);

    // ----- State evaluation methods -----

    /**
     * Evaluate a character with the normal state actions
     *
     * @param charToEval The char to eval
     */
    void evalNormal(char charToEval);

    /**
     * Evaluate a character with the string state actions
     *
     * @param charToEval The character to eval
     */
    void evalString(char charToEval);

    /**
     * Evaluate a character with the one line comment state
     *
     * @param charToEval The character to eval
     */
    void evalOneLineComment(char charToEval);

    /**
     * Evaluate a character with the multi line comment state
     *
     * @param charToEval The character to eval
     */
    void evalMultiLineComment(char charToEval);

    // ----- Lexical analyzer starting methods -----

    /**
     * Do the lexical analysis in once
     *
     * !!! Critical performance - use low level C functions !!!
     *
     * @throws LexingException If the file contains lexical errors
     */
    void doLexInOnce();

public:

    // ----- Constructors -----

    /**
     * Construct a new lexer with the wanted file
     *
     * @param inputFile The pointer to the file you want to lex
     * @throws FileException If the file is unreadable
     */
    explicit Lexer(const std::string &file);

    // ----- Destructor -----

    ~Lexer();

    // ----- Getters -----

    /**
     * Get the lexing result in a vector by copying it, force the lexical analysis in once
     *
     * @param result The vector you want to store the result in
     * @throws Exception if the lexical analysis has failed
     */
    void getLexResult(std::vector<Token> &result);

    /**
     * Get the next token in the file
     *
     * @param result The token to return
     * @throws Exception if the lexical analysis has failed
     */
    void getNextToken(Token &result);
};

#endif // CPP_WOL_LEXER_H
