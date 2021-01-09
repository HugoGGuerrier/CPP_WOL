#include <regex>
#include <cstdio>
#include <cstdlib>
#include <tools/Config.h>

#include "lexer/Lexer.h"
#include "tools/Utils.h"
#include "Lexenv.h"

#include "exceptions/FileException.h"
#include "exceptions/LexingException.h"

// ----- Constructors -----

Lexer::Lexer(const std::string &file) {
    this->file = file;

    // Open the file to lex
    this->lexerData.file = fopen(this->file.c_str(), "r");

    // Verify the file
    if(this->lexerData.file == nullptr) {
        throw FileException("Lexer", "doLexInOnce", "File " + this->file + " is missing or unreadable. Cannot continue lexing.");
    }

    // Initialize attributes
    this->resultPointer = 0;

    // Initialize the lexical analysis
    this->lexerData.buffer = (char *)malloc(Config::maxWordSize * sizeof(char));
    memset(this->lexerData.buffer, 0, Config::maxWordSize * sizeof(char));
    this->lexerData.currentState = Lexer::NORMAL_STATE;
}

// ----- Destructor -----

Lexer::~Lexer() {
    this->lexResult.clear();
    free(this->lexerData.buffer);
    fclose(this->lexerData.file);
}

// ----- Internal methods -----

char Lexer::getNextChar() {
    return '0';
}

void Lexer::doBufferLexing() {
    // Get the token code with the lexical environment
    int tokenCode = Lexenv::getLexicalTokenCode(this->lexerData.buffer);

    // If the token code is known, add the token to the result, else raise an error
    if(tokenCode != -1) {

        // Prepare the size of the string to add in the token
        unsigned int size;

        // This switch handle all token with necessary value (int, char, identifier...)
        switch (tokenCode) {

            // If the token is a int value, a float value or a identifier
            case Lexenv::INT_VAL:
            case Lexenv::FLOAT_VAL:
            case Lexenv::IDENTIFIER:
                size = this->lexerData.bufferPointer;
                break;

            // If the value is a character value
            case Lexenv::CHAR_VAL:
                // All char have a size of 1
                size = 1;

                // Test if the char is escaped or not
                if(this->lexerData.buffer[1] == '\\') {

                    int intC = getEscapedChar(this->lexerData.buffer[2]);
                    if(intC != -1) {
                        this->lexerData.buffer[0] = (char)intC;
                    } else {
                        this->raiseError("Unknown escaped sequence", 1);
                    }

                } else {

                    this->lexerData.buffer[0] = this->lexerData.buffer[1];

                }

                break;

            default:
                size = 0;
                break;

        }

        // Prepare the positions
        unsigned int sPos = this->lexerData.currentPos - this->lexerData.bufferPointer;
        unsigned int ePos = this->lexerData.currentPos;

        // Add the token to the result
        this->addToken(tokenCode, sPos, ePos, this->lexerData.buffer, size);

    } else {

        // If the symbol is not know, just raise a lexical error
        this->raiseError("Unknown symbol", this->lexerData.bufferPointer);

    }

    // Reset the buffer
    memset(this->lexerData.buffer, 0, Config::maxWordSize * sizeof(char));
    this->lexerData.bufferPointer = 0;
}

void Lexer::updatePosition(char charToEval) {
    // Increase the current position
    this->lexerData.currentPos++;

    // Increase the line number
    if(charToEval == '\n' && !this->lexerFlags.CARRIAGE_NEWLINE) {
        this->lexerData.currentLine++;
        this->lexerData.currentPos = 1;
    } else if(charToEval == '\r') {
        this->lexerData.currentLine++;
        this->lexerData.currentPos = 1;
        this->lexerFlags.CARRIAGE_NEWLINE = true;
    }
}

void Lexer::raiseError(const std::string &message, unsigned int offset) {
    this->lexerFlags.ERROR_FLAG = true;
    this->lexerData.errorLine = this->lexerData.currentLine;
    this->lexerData.errorPos = this->lexerData.currentPos - offset;
    this->lexerData.errorMessage = message;
}

void Lexer::addToken(int tokenId, unsigned int startPos, unsigned int endPos, const char *value, unsigned int size) {
    Token newToken;
    newToken.setId(tokenId);
    newToken.setStartPos(startPos);
    newToken.setEndPos(endPos);
    newToken.setLine(this->lexerData.currentLine);
    newToken.setValue(value, size);
    this->lexResult.emplace_back(newToken);
}

// ----- State evaluation methods -----

void Lexer::evalNormal(char charToEval) {
    // --- Flag resetting

    if(this->lexerFlags.COMMENT_START_FLAG) {
        if(charToEval != '/' && charToEval != '*') {
            this->addToken(Lexenv::DIVIDE, this->lexerData.currentPos - 1, this->lexerData.currentPos);
            this->lexerFlags.COMMENT_START_FLAG = false;
        }
    }

    // --- Stop char handling

    int stopCharCode = Lexenv::getStopCharCode(charToEval);

    if(stopCharCode != -1) {

        // If the buffer is not empty, evaluate the buffer
        if(this->lexerData.bufferPointer != 0) {
            this->doBufferLexing();
        }

        // Special stop char cases
        switch (stopCharCode) {
            case Lexenv::BLANK:
            case Lexenv::EOF_SYMBOL:
                // Do nothing
                break;

            case Lexenv::DIVIDE:
                // When a divide is encountered, set the comment flag to true
                if(!this->lexerFlags.COMMENT_START_FLAG) {
                    this->lexerFlags.COMMENT_START_FLAG = true;
                } else {
                    this->lexerData.currentState = Lexer::ONE_LINE_COMMENT_STATE;
                    this->lexerFlags.COMMENT_START_FLAG = false;
                }
                break;

            case Lexenv::TIMES:
                // When a times is encountered, if the comment start flag is true, enter the multiline comment state
                if(this->lexerFlags.COMMENT_START_FLAG) {
                    this->lexerData.currentState = Lexer::MULTI_LINE_COMMENT_STATE;
                    this->lexerFlags.COMMENT_START_FLAG = false;
                } else {
                    this->addToken(Lexenv::TIMES, this->lexerData.currentPos, this->lexerData.currentPos + 1);
                }
                break;

            case Lexenv::QUOTE:
                this->lexerData.currentState = Lexer::STRING_STATE;
                break;

            default:
                this->addToken(stopCharCode, this->lexerData.currentPos, this->lexerData.currentPos + 1);
                break;
        }

    } else {

        // If the char isn't a stop char, just put it into the buffer, before verify the buffer size
        if(this->lexerData.bufferPointer >= Config::maxWordSize) {

            this->raiseError("A word exceed the maximum size", this->lexerData.bufferPointer);

        } else {

            this->lexerData.buffer[this->lexerData.bufferPointer++] = charToEval;

        }

    }
}

void Lexer::evalString(char charToEval) {
    if (charToEval == '\n' || (charToEval == '\r' && this->lexerFlags.CARRIAGE_NEWLINE) || charToEval == EOF_CHAR) {

        // Handle the unfinished string error
        this->raiseError("Unfinished string value", this->lexerData.stringValueBuffer.size() + 1);

    } else if(this->lexerFlags.NEXT_ESCAPED_FLAG) {

        // Reset the flag
        this->lexerFlags.NEXT_ESCAPED_FLAG = false;

        // Handle the possibly escaped chars
        int cInt = getEscapedChar(charToEval);
        if(cInt == -1) {
            this->raiseError("Unknown escaped sequence", 1);
        } else {
            this->lexerData.stringValueBuffer.push_back((char) cInt);
        }

    } else {

        // Append the characters
        if(charToEval ==  '"') {
            unsigned int startPos = this->lexerData.currentPos - this->lexerData.stringValueBuffer.size();
            unsigned int endPos = this->lexerData.currentPos;
            this->addToken(Lexenv::STRING_VAL, startPos, endPos, this->lexerData.stringValueBuffer.c_str(), this->lexerData.stringValueBuffer.size());

            // Clear the buffer
            this->lexerData.stringValueBuffer.clear();
            this->lexerData.currentState = Lexer::NORMAL_STATE;
        } else if(charToEval == '\\') {
            this->lexerFlags.NEXT_ESCAPED_FLAG = true;
        } else {
            this->lexerData.stringValueBuffer.push_back(charToEval);
        }

    }
}

void Lexer::evalOneLineComment(char charToEval) {
    if(charToEval == '\n' || (charToEval == '\r' && this->lexerFlags.CARRIAGE_NEWLINE) || charToEval == EOF_CHAR)
        this->lexerData.currentState = Lexer::NORMAL_STATE;
}

void Lexer::evalMultiLineComment(char charToEval) {
    if(charToEval == '*') {

        this->lexerFlags.COMMENT_MULTILINE_END_FLAG = true;

    } else if(this->lexerFlags.COMMENT_MULTILINE_END_FLAG) {

        if (charToEval == '/') this->lexerData.currentState = NORMAL_STATE;
        this->lexerFlags.COMMENT_MULTILINE_END_FLAG = false;

    }
}

// ----- Lexical analyzer starting methods -----

void Lexer::doLexInOnce() {
    // Temporary variables
    int charToEvalInt = '\0';

    while(charToEvalInt != EOF && !this->lexerFlags.ERROR_FLAG) {

        // Get the next char int value (EOF is -1)
        charToEvalInt = fgetc(this->lexerData.file);

        // If EOF, set the done flag
        if(charToEvalInt == EOF) {
            this->lexerFlags.LEXING_FINISH = true;
        }

        // Get the real char to evaluate it
        char realChar = charToEvalInt != EOF ? (char) charToEvalInt : EOF_CHAR;

        // Switch the current state to evaluate the next character
        switch (this->lexerData.currentState) {

            case Lexer::NORMAL_STATE:

                // Handle the current character normally
                this->evalNormal(realChar);

                break;

            case Lexer::STRING_STATE:

                // Eval the character with the string state
                this->evalString(realChar);

                break;

            case Lexer::ONE_LINE_COMMENT_STATE:

                // Eval the character with the one line comment state
                this->evalOneLineComment(realChar);

                break;

            case Lexer::MULTI_LINE_COMMENT_STATE:

                // Eval the character with the multi line comment state
                this->evalMultiLineComment(realChar);

                break;

            default:
                this->raiseError("Lexer state is not referenced", 0);
                break;

        }

        // Update the file position
        Lexer::updatePosition(realChar);

    }

    // Verify the buffer states
    if((this->lexerData.bufferPointer != 0 || !this->lexerData.stringValueBuffer.empty()) && !this->lexerFlags.ERROR_FLAG) {
        this->raiseError("Cannot parse the file, lexical analyser must have a problem", 0);
    }

    // Handle errors
    if(this->lexerFlags.ERROR_FLAG) {
        std::string message = "File : " + this->file + " [" + std::to_string(this->lexerData.errorLine) + ":" + std::to_string(this->lexerData.errorPos) + "] | " + this->lexerData.errorMessage;
        throw LexingException(message);
    }
}

// ----- Getters -----

void Lexer::getLexResult(std::vector<Token> &result) {
    // Finish the lexing of not
    if(!this->lexerFlags.LEXING_FINISH) {
        this->doLexInOnce();
    }

    // Clear the result vector
    result.clear();

    // Copy all tokens in the result vector
    result = this->lexResult;
}

const Token *Lexer::getNextToken() {
    if(Config::lazyLexer) {

        // TODO : Make the lazy lexing
        return nullptr;

    } else {

        // If the lexer is not lazy
        if(!this->lexerFlags.LEXING_FINISH) this->doLexInOnce();

        if(this->resultPointer < this->lexResult.size()) {
            return &(this->lexResult[this->resultPointer++]);
        } else {
            return nullptr;
        }

    }
}