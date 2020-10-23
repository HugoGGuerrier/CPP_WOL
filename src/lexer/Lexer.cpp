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
}

// ----- Destructor -----

Lexer::~Lexer() {
    this->lexResult.clear();
}

// ----- Internal methods -----

void Lexer::evalNormal(char charToEval) {
    // --- Flag reseting

    if(this->lexerFlags.COMMENT_START_FLAG) {
        if(charToEval != '/' && charToEval != '*') {
            this->addToken(Lexenv::DIVIDE, this->lexerData.currentPos - 1, this->lexerData.currentPos, this->lexerData.currentLine);
            this->lexerFlags.COMMENT_START_FLAG = false;
        }
    }

    // --- Stop char handling

    int stopCharCode = Lexenv::getStopCharCode(charToEval);

    if(stopCharCode != -1) {

        // If the buffer is not empty, evaluate the buffer
        if(this->lexerData.bufferPointer != 0) {
            this->evalBuffer();
        }

        // Special stop char cases
        switch (stopCharCode) {
            case Lexenv::BLANK:
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
                    this->addToken(Lexenv::TIMES, this->lexerData.currentPos, this->lexerData.currentPos + 1, this->lexerData.currentLine);
                }
                break;

            case Lexenv::QUOTE:
                this->lexerData.currentState = Lexer::STRING_STATE;
                break;

            default:
                this->addToken(stopCharCode, this->lexerData.currentPos, this->lexerData.currentPos + 1, this->lexerData.currentLine);
                break;
        }

    } else {

        // Verify the buffer size
        if(this->lexerData.bufferPointer >= Config::maxWordSize) {
            this->raiseError("A word exceed the maximum size", this->lexerData.currentLine, this->lexerData.currentPos - this->lexerData.bufferPointer);
        } else {

            // If the char isn't a stop char, just put it into the buffer
            this->lexerData.buffer[this->lexerData.bufferPointer++] = charToEval;

        }


    }
}

void Lexer::evalString(char charToEval) {
    if (charToEval == '\n' || charToEval == '\r' || charToEval == EOF_CHAR) {

        // Handle the unfinished string error
        unsigned int position = this->lexerData.currentPos - this->lexerData.stringValueBuffer.length() - 1;
        this->raiseError("Unfinished string value", this->lexerData.currentLine, position);

    } else if(this->lexerFlags.NEXT_ESCAPED_FLAG) {

        // Handle the possibly escaped chars
        int escapedCharInt = getEscapedChar(charToEval);
        if(escapedCharInt == -1) {
            this->raiseError("Unknown escaped sequence", this->lexerData.currentLine, this->lexerData.currentPos - 2);
        } else {
            this->lexerData.stringValueBuffer.push_back((char)escapedCharInt);
        }

    } else {

        // Append the chars
        if(charToEval ==  '"') {
            unsigned int startPos = this->lexerData.currentPos - this->lexerData.stringValueBuffer.size();
            unsigned int endPos = this->lexerData.currentPos;
            this->addToken(Lexenv::STRING_VAL, startPos, endPos, this->lexerData.currentLine, this->lexerData.stringValueBuffer.c_str(), this->lexerData.stringValueBuffer.size());

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

void Lexer::evalBuffer() {
    // Get the token code
    int tokenCode = Lexenv::getLexicalTokenCode(this->lexerData.buffer);

    // If the token code is known, add the token to the result, else raise an error
    if(tokenCode != -1) {

        // Prepare the value buffer
        unsigned int size;

        switch (tokenCode) {

            case Lexenv::NUMBER_VAL:
            case Lexenv::IDENTIFIER:
                size = this->lexerData.bufferPointer;
                break;

            case Lexenv::CHAR_VAL:
                if(this->lexerData.buffer[1] == '\\') {
                    int intC = getEscapedChar(this->lexerData.buffer[2]);
                    if(intC != -1) {
                        this->lexerData.buffer[0] = (char)intC;
                    } else {
                        this->raiseError("Unknown escaped sequence", this->lexerData.currentLine, this->lexerData.currentPos - 4);
                    }
                } else {
                    this->lexerData.buffer[0] = this->lexerData.buffer[1];
                }
                size = 1;
                break;

            default:
                size = 0;
                break;

        }

        // Prepare the positions
        unsigned int sPos = this->lexerData.currentPos - this->lexerData.bufferPointer;
        unsigned int ePos = this->lexerData.currentPos;
        unsigned int line = this->lexerData.currentLine;

        // Add the token to the result
        this->addToken(tokenCode, sPos, ePos, line, this->lexerData.buffer, size);

    } else {

        this->raiseError("Unknown symbol", this->lexerData.currentLine, this->lexerData.currentPos - this->lexerData.bufferPointer);

    }

    // Reset the buffer
    memset(this->lexerData.buffer, 0, Config::maxWordSize * sizeof(char));
    this->lexerData.bufferPointer = 0;
}

void Lexer::updatePosition(char charToEval) {
    // Increase the current position
    this->lexerData.currentPos++;

    // Compatibility with windows written files
    if(this->lexerFlags.WINDOWS_NEW_LINE_FLAG && charToEval != '\n') {
        this->lexerFlags.WINDOWS_NEW_LINE_FLAG = false;
    }

    // Increase the line number
    if(charToEval == '\n' && !this->lexerFlags.WINDOWS_NEW_LINE_FLAG) {
        this->lexerData.currentPos = 1;
        this->lexerData.currentLine++;
    } else if(charToEval == '\r') {
        this->lexerData.currentPos = 1;
        this->lexerData.currentLine++;
        this->lexerFlags.WINDOWS_NEW_LINE_FLAG = true;
    }
}

void Lexer::raiseError(const std::string &message, unsigned int line, unsigned int pos) {
    this->lexerFlags.ERROR_FLAG = true;
    this->lexerData.errorLine = line;
    this->lexerData.errorPos = pos;
    this->lexerData.errorMessage = message;
}

void Lexer::addToken(int tokenId, unsigned int startPos, unsigned int endPos, unsigned int line, const char *value, unsigned int size) {
    Token newToken;
    newToken.setId(tokenId);
    newToken.setStartPos(startPos);
    newToken.setEndPos(endPos);
    newToken.setLine(line);
    newToken.setValue(value, size);
    this->lexResult.emplace_back(newToken);
}

// ----- Getters -----

void Lexer::getLexResult(std::vector<Token> &result) const {
    // Clear the result vector
    result.clear();

    // Copy all tokens in the result vector
    result = this->lexResult;
}

// ----- Class methods -----

void Lexer::doLex() {
    // Verify if the file was already lexed
    if(this->lexResult.empty()) {

        // Open the file to lex
        FILE *fileToLex;
        fileToLex = fopen(this->file.c_str(), "r");

        // Verify the file
        if(fileToLex == nullptr) {
            throw FileException("Lexer", "doLex", "File " + this->file + " is missing or unreadable. Cannot continue lexing.");
        }

        // Initialize the lexical analysis
        this->lexerData.buffer = (char *)malloc(Config::maxWordSize * sizeof(char));
        memset(this->lexerData.buffer, 0, Config::maxWordSize * sizeof(char));
        this->lexerData.currentState = Lexer::NORMAL_STATE;

        // Temporary variables
        int charToEvalInt = '\0';

        while(charToEvalInt != EOF && !this->lexerFlags.ERROR_FLAG) {
            charToEvalInt = fgetc(fileToLex);
            char realChar = charToEvalInt != EOF ? (char) charToEvalInt : EOF_CHAR;

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

                    // If there is a carriage return reset the state to normal
                    if(realChar == '\n' || realChar == '\r') this->lexerData.currentState = Lexer::NORMAL_STATE;

                    break;

                case Lexer::MULTI_LINE_COMMENT_STATE:

                    // Handle the multiline comment end adn return to normal state
                    if(realChar == '*') {

                        this->lexerFlags.COMMENT_MULTILINE_END_FLAG = true;

                    } else if(this->lexerFlags.COMMENT_MULTILINE_END_FLAG) {

                        if (realChar == '/') this->lexerData.currentState = NORMAL_STATE;
                        this->lexerFlags.COMMENT_MULTILINE_END_FLAG = false;

                    }

                    break;

                default:
                    this->raiseError("Lexer state is not referenced", 1, 1);
                    break;

            }

            // Update the file position
            Lexer::updatePosition(realChar);

        }

        // Close the file and clean memory
        free(this->lexerData.buffer);
        fclose(fileToLex);

        // Handle errors
        if(this->lexerFlags.ERROR_FLAG) {
            std::string message = "File : " + this->file + " [" + std::to_string(this->lexerData.errorLine) + ":" + std::to_string(this->lexerData.errorPos) + "] | " + this->lexerData.errorMessage;
            throw LexingException(message);
        }

    }
}