#include "lexer/Lexer.h"
#include "Lexenv.h"

#include "exceptions/FileException.h"
#include "exceptions/LexingException.h"

// ----- Constructors -----

Lexer::Lexer(const std::string &file) {
    this->file = file;
}

// ----- Internal methods -----

int Lexer::processString(const std::string &stringToProcess) const {
    return -1;
}

void Lexer::addToken(int tokenId, int startPos, int endPos, int line) {
    std::cout << std::to_string(tokenId) << std::endl;
    // TODO
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
    // Open the file to lex
    std::ifstream fileToLex;
    fileToLex.open(this->file);

    // Verify the file
    if(!fileToLex.is_open()) {
        throw FileException("Lexer", "doLex", "File " + this->file + " is missing or unreadable. Cannot continue lexing.");
    }

    // Process each line
    std::string line;
    int currentLine = 1;

    while(std::getline(fileToLex, line)) {

        // Create the line buffer to extract tokens from the line with the position
        std::string lineBuffer;
        int lastTokenFound = -1;
        int startPos = 1;

        // For each char, buf it into a string an extract tokens from it
        for(int i = 0; i < line.size(); i++) {

            // Construct the new string and process it
            lineBuffer.append(line.substr(i, 1));
            int processResult = this->processString(lineBuffer);

            // Verify the process result
            if(processResult != -1) {
                lastTokenFound = processResult;
            } else {
                if(lastTokenFound != -1) {
                    this->addToken(lastTokenFound, startPos, i, currentLine);
                    lineBuffer.clear();
                    lastTokenFound = -1;
                    startPos = i;
                }
            }

        }

        // Verify that all the line was lexed
        if(!lineBuffer.empty()) {
            throw LexingException("Lexer", "doLex", "Unknown symbol in source file : " + this->file + " at line " + std::to_string(currentLine) + ":" + std::to_string(startPos) + ". Cannot continue lexing.");
        }

        // Increase line counter
        currentLine++;

    }

    // Close the file
}
