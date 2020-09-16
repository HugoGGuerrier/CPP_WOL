#ifndef CPP_WOL_LEXERTESTS_H
#define CPP_WOL_LEXERTESTS_H

#include <fstream>

#include "TestBase.h"

/**
 * This class contains all tests for the lexer
 */
class LexerTests: public TestBase {
private:

    // ----- Attributes -----

    /**
     * The file to test the lexer
     */
    std::ifstream testFile;

public:

    // ----- Constructors -----

    /**
     * The constructor of the lexer tests
     */
    LexerTests();

    // ----- Class methods -----

    /**
     * The tests for the lexer
     *
     * @return The exit code of the tests
     */
    int run() const override;
};


#endif // CPP_WOL_LEXERTESTS_H
