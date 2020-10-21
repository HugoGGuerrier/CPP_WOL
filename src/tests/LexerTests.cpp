#include "LexerTests.h"
#include "lexer/Lexer.h"

#include "exceptions/LexingException.h"
#include "exceptions/FileException.h"

// ----- Constructors -----

LexerTests::LexerTests() {
    this->init(2);
}

// ----- Class methods -----

int LexerTests::run(){
    // Create the lexers for the tests
    Lexer lexer1(LexerTests::testFile1);
    Lexer lexer2(LexerTests::testFile2);

    // --- Run the test 1 that should succeed

    try {

        // Start the test 1
        this->startTest(1);

        // Lex the file
        lexer1.doLex();

        this->succeedTest(1, "File successfully lexed !");

    } catch (FileException &e) {

        // Fail the test
        this->failTest(1, e.what());

    } catch (LexingException &e) {

        // Fail the test
        this->failTest(1, e.what());

    }

    // --- Run the test 2 that should fail

    try {

        // Start the test
        this->startTest(2);

        // Lex the file
        lexer2.doLex();

        // If this code is executed that the Lexer failed
        this->failTest(2, "Expected to fail lexing !");

    } catch (LexingException &e) {

        // Nothing just success
        this->succeedTest(2, e.what());

    } catch (FileException &e) {

        // Log the error
        this->failTest(2, e.what());

    }

    // Return the result
    return this->verifyTests();
}