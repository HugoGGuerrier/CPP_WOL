#include <memory>

#include "LexerTests.h"
#include "lexer/Lexer.h"

#include <exceptions/LexingException.h>
#include "exceptions/FileException.h"

// ----- Constructors -----

LexerTests::LexerTests() {
    this->init(2);
}

// ----- Class methods -----

int LexerTests::run(){
    // Create the lexers for the tests
    auto lexer1 = std::make_unique<Lexer>(Lexer(LexerTests::testFile1));
    auto lexer2 = std::make_unique<Lexer>(Lexer(LexerTests::testFile2));

    // --- Run the test 1 that should succeed

    try {

        // Lex the file
        lexer1->doLex();

        this->succeedTest(1);

    } catch (FileException &e) {

        // Log the exception in the logger
        Logger::log_test_err(e.what());
        this->failTest(1);

    } catch (LexingException &e) {

        // Log the exception in the logger
        Logger::log_test_err(e.what());
        this->failTest(1);

    }

    // --- Run the test 2 that should fail

    try {

        // Lex the file
        lexer2->doLex();

        // If this code is executed that the Lexer failed
        this->failTest(2);

    } catch (LexingException &e) {

        // Nothing just success
        this->succeedTest(2);

    } catch (FileException &e) {

        // Log the error
        Logger::log_test_err(e.what());
        this->failTest(2);

    }

    // Return the result
    return this->verifyTests();
}