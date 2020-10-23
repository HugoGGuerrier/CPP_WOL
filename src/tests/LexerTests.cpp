#include "tools/Utils.h"
#include "LexerTests.h"
#include "lexer/Lexer.h"

#include "exceptions/LexingException.h"
#include "exceptions/FileException.h"

// ----- Constructors -----

LexerTests::LexerTests() {
    this->init(4);
}

// ----- Class methods -----

int LexerTests::run(){
    // Create the lexers for the tests
    Lexer lexer1(LexerTests::testFile1);
    Lexer lexer2(LexerTests::testFile2);
    Lexer lexer3(LexerTests::testFile3);
    Lexer lexer4(LexerTests::testFile4);

    // --- Run the test 1 that should succeed

    try {

        // Start the test 1
        this->startTest(1);

        // Lex the file
        lexer1.doLex();

        // Verify the result
        std::vector<Token> res;
        lexer1.getLexResult(res);

        this->succeedTest("File successfully lexed ! " + vectos(res));

    } catch (FileException &e) {

        // Fail the test
        this->failTest(e.what());

    } catch (LexingException &e) {

        // Fail the test
        this->failTest(e.what());

    }

    // --- Run the test 2 that should fail

    try {

        // Start the test
        this->startTest(2);

        // Lex the file
        lexer2.doLex();

        // If this code is executed that the Lexer failed
        this->failTest("Expected to fail lexing !");

    } catch (LexingException &e) {

        // Nothing just success
        this->succeedTest(e.what());

    } catch (FileException &e) {

        // Log the error
        this->failTest(e.what());

    }

    // --- Run the test 3 that should fail

    try {

        // Start the test
        this->startTest(3);

        // Lex the file
        lexer3.doLex();

        // If this code is executed that the Lexer failed
        this->failTest("Expected to fail lexing !");

    } catch (LexingException &e) {

        this->succeedTest(e.what());

    } catch (FileException &e) {

        this->failTest(e.what());

    }

    // --- Run the test 4 that should fail

    try {

        // Start the test
        this->startTest(4);

        // Lex the file
        lexer4.doLex();

        // If this code is executed that the Lexer failed
        this->failTest("Expected to fail lexing !");

    } catch (LexingException &e) {

        this->succeedTest(e.what());

    } catch (FileException &e) {

        this->failTest(e.what());

    }

    // Return the result
    return this->verifyTests();
}