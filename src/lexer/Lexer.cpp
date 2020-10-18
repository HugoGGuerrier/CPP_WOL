#include <regex>
#include <cstdio>
#include <cstdlib>
#include <tools/Config.h>

#include "lexer/Lexer.h"
#include "Lexenv.h"

#include "exceptions/FileException.h"
#include "exceptions/LexingException.h"

// ----- Constructors -----

Lexer::Lexer(const std::string &file) {
    this->file = file;
}

// ----- Internal methods -----

void Lexer::evalChar(char charToEval, lexer_data *data) {
    int stopCharCode = Lexer::getStopCharCode(charToEval);

    if(stopCharCode != -1) {

        // If the buffer is not empty, evaluate the buffer
        if(data->bufferPointer != 0) {
            // Get the token code
            int tokenCode = Lexer::getLexicalTokenCode(data->buffer);

            // Reset the buffer
            memset(data->buffer, 0, Config::maxWordSize * sizeof(char));
            data->bufferPointer = 0;

            // TODO : Add the token to the result
        }

        // Special stop char cases
        switch (stopCharCode) {
            case Lexenv::BLANK:
                // Do nothing
                break;

            case Lexenv::DIVIDE:
                // When a divide is encountered, set the comment flag to true
                if(!data->COMMENT_START_FLAG) {
                    data->COMMENT_START_FLAG = true;
                } else {
                    data->currentState = Lexer::ONE_LINE_COMMENT_STATE;
                    data->COMMENT_START_FLAG = false;
                }
                break;

            case Lexenv::TIMES:
                // When a times is encountered, if the comment start flag is true, enter the multiline comment state
                if(data->COMMENT_START_FLAG) {
                    data->currentState = Lexer::MULTI_LINE_COMMENT_STATE;
                    data->COMMENT_START_FLAG = false;
                } else {
                    // TODO : Add the token to the result
                }
                break;

            case Lexenv::QUOTE:
                data->currentState = Lexer::STRING_STATE;
                break;

            default:
                // TODO : Add the token to the result
                break;
        }

    } else {

        // If the char isn't a stop char, just put it into the buffer
        data->buffer[data->bufferPointer++] = charToEval;

    }
}

void Lexer::updatePosition(char charToEval, lexer_data *data) {
    // Increase the current position
    data->currentPos++;

    // Compatibility with windows written files
    if(data->WINDOWS_NEW_LINE_FLAG && charToEval != '\n') {
        data->WINDOWS_NEW_LINE_FLAG = false;
    }

    // Increase the line number
    if(charToEval == '\n' && !data->WINDOWS_NEW_LINE_FLAG) {
        data->currentPos = 1;
        data->currentLine++;
    } else if(charToEval == '\r') {
        data->currentPos = 1;
        data->currentLine++;
        data->WINDOWS_NEW_LINE_FLAG = true;
    }
}

int Lexer::getStopCharCode(char charToTest) {
    for(int i = 0; i < Lexenv::stopCharNumber; i++) {
        if(charToTest == Lexenv::stopCharArray[i]) return Lexenv::stopCharCode[i];
    }
    return -1;
}

int Lexer::getLexicalTokenCode(char *strToTest) {
    for(int i = 0; i < Lexenv::regexNumber; i++) {
        if(regexec(&Lexenv::regexTArray[i], strToTest, 0, nullptr, 0) == 0) return Lexenv::regexCode[i];
    }
    return -1;
}

void Lexer::addToken(int tokenId, int startPos, int endPos, int line, const char *value) {
    Token newToken;
    newToken.setStartPos(startPos);
    newToken.setEndPos(endPos);
    newToken.setLine(line);
    newToken.setValue(value);
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
        FILE *fileToLex = nullptr;
        fileToLex = fopen(this->file.c_str(), "r");

        // Verify the file
        if(fileToLex == nullptr) {
            throw FileException("Lexer", "doLex", "File " + this->file + " is missing or unreadable. Cannot continue lexing.");
        }

        // Initialize the lexical analysis
        lexer_data data;
        data.buffer = (char *)malloc(Config::maxWordSize * sizeof(char));
        memset(data.buffer, 0, Config::maxWordSize * sizeof(char));
        data.currentState = Lexer::NORMAL_STATE;

        char charToEval;

        while((charToEval = (char)fgetc(fileToLex)) != EOF) {

            switch (data.currentState) {

                case Lexer::NORMAL_STATE:
                    this->evalChar(charToEval, &data);
                    break;

                case Lexer::STRING_STATE:
                    // TODO : The lexer behavior for a string value
                    break;

                case Lexer::ONE_LINE_COMMENT_STATE:
                    // If there is a carriage return reset the state to normal
                    if(charToEval == '\n' || charToEval == '\r') {
                        data.currentState = Lexer::NORMAL_STATE;
                    }
                    break;

                case Lexer::MULTI_LINE_COMMENT_STATE:
                    // Handle the multiline comment end adn return to normal state
                    if(charToEval == '*') {
                        data.COMMENT_MULTILINE_END_FLAG = true;
                    } else if(data.COMMENT_MULTILINE_END_FLAG) {
                        if (charToEval == '/') data.currentState = NORMAL_STATE;
                        data.COMMENT_MULTILINE_END_FLAG = false;
                    }
                    break;

                default:
                    throw LexingException("Lexer", "doLex", "Lexer state is not referenced !");

            }

            // Update the file position
            updatePosition(charToEval, &data);


        }

        // Close the file and clean memory
        free(data.buffer);
        fclose(fileToLex);

    }
}