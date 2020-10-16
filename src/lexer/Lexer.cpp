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

int Lexer::getStopCharCode(char charToTest) {
    for(int i = 0; i < Lexenv::stopCharNumber; i++) {
        if(charToTest == Lexenv::stopCharArray[i]) return Lexenv::stopCharCode[i];
    }
    return -1;
}

int Lexer::getLexicalTokenCode(char *strToTest) {
    return 0;
}

void Lexer::addToken(int tokenId, int startPos, int endPos, int line, const char *value) {
    auto newToken = std::make_unique<Token>(Token(tokenId));
    newToken->setStartPos(startPos);
    newToken->setEndPos(endPos);
    newToken->setLine(line);
    newToken->setValue(value);
    this->lexResult.emplace_back();
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
        char nextChar;
        char *buffer = (char *)malloc(Config::maxWordSize * sizeof(char));
        int currentState = Lexer::NORMAL_STATE;

        int bufferPointer = 0;
        int currentLine = 1;
        int currentPos = 1;

        bool windowsNewlineCompatFlag = false;

        while((nextChar = (char)fgetc(fileToLex)) != EOF) {
            if(currentState == Lexer::NORMAL_STATE) {

                int stopCharCode = this->getStopCharCode(nextChar);
                if(stopCharCode != -1) {

                    // If the char is a stop char
                    if(bufferPointer != 0) {
                        int tokenCode = Lexer::getLexicalTokenCode(buffer);
                    } else {

                    }

                } else {

                    // If the char isn't a stop char, just put it into the buffer
                    buffer[bufferPointer] = nextChar;

                }

            } else if(currentState == Lexer::ONE_LINE_COMMENT_STATE) {

                // If there is a carriage return reset the state to normal
                if(nextChar == '\n' || nextChar == '\r') {
                    currentState = Lexer::NORMAL_STATE;
                }

            } else if(currentState == Lexer::MULTI_LINE_COMMENT_STATE) {

                // If there is the end of the comment reset state to normal
                if(nextChar == '*') {
                    nextChar = (char)getc(fileToLex);
                    currentPos++;
                    if(nextChar == '/') {
                        currentState = Lexer::NORMAL_STATE;
                    }
                }

            }

            // Increase the current position
            currentPos++;

            // Compatibility with windows written files
            if(windowsNewlineCompatFlag && nextChar != '\n') {
                windowsNewlineCompatFlag = false;
            }

            // Increase the line number
            if(nextChar == '\n' && !windowsNewlineCompatFlag) {
                currentPos = 1;
                currentLine++;
            } else if(nextChar == '\r') {
                currentPos = 1;
                currentLine++;
                windowsNewlineCompatFlag = true;
            }
        }

        std::cout << std::to_string(currentLine) << ":" << std::to_string(currentPos) << std::endl;

        // TODO : Use low level function fopen() to read the file char by char

        // TODO : Do the lexing process and store it into the lexing result

        // Close the file
        fclose(fileToLex);

    }
}