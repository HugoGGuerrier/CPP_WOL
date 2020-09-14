#include "lexer/Lexer.h"

// ----- Constructors -----

Lexer::Lexer(std::ifstream *inputFile) {
    this->inputFile = inputFile;
    this->lexResult = new std::vector<Token>;
}

// ----- Getters -----

std::vector<Token> & Lexer::getLexResult() {
    return *this->lexResult;
}

// ----- Class methods -----

int Lexer::doLex() {
    return 0;
}