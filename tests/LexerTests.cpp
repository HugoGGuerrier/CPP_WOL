#include <iostream>

#include "LexerTests.h"

// ----- Constructors -----

LexerTests::LexerTests() {
    this->testFile.open("");
}

// ----- Class methods -----

int LexerTests::run() const{
    // Verify the test file
    if(!this->testFile.is_open()) {
        Logger::log_test_err("Cannot open the lexer tests file !");
        return 1;
    }

    std::cout << "LexerTests run method" << std::endl;

    return 0;
}