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
    // Loop over the files to tests to test the lexical analyser
    for(int i = 0; i < this->testNumber + 1; i++) {
        // Create the wanted lexer
        Lexer lexer(Config::basePath + LexerTests::testFiles[i]);

        // Start the test
        this->startTest(i);

        try {

            lexer.doLex();

            std::vector<Token> res;
            lexer.getLexResult(res);

            if(LexerTests::expectedBahvior[i] == SUCCESS) this->succeedTest("File sucessfully lexed ! " + vectos(res));
            else this->failTest("Test is expected to fail !");

        } catch (LexingException &e) {

            if(LexerTests::expectedBahvior[i] == FAILURE) this->succeedTest(e.what());
            else this->failTest(e.what());

        } catch (FileException &e) {

            this->failTest(e.what());

        }
    }

    // Return the result
    return this->verifyTests();
}