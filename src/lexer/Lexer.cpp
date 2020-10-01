#include "lexer/Lexer.h"
#include "Lexenv.h"

#include "exceptions/FileException.h"

// ----- Constructors -----

Lexer::Lexer(const std::string &file) {
    this->file = file;
}

// ----- Internal methods -----

void Lexer::processString(const std::string &stringToProcess, Token &resultToken) const {

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
    auto fileToLex = std::make_unique<std::ifstream>(std::ifstream());
    fileToLex->open(this->file);

    // Verify the file
    if(!fileToLex->is_open()) {
        throw FileException("Lexer", "doLex", "File " + this->file + " is missing or unreadable. Cannot continue lexing.");
    }

    // Process each line

    // Close the file
}
