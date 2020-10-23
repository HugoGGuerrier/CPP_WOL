#ifndef CPP_WOL_LEXERTESTS_H
#define CPP_WOL_LEXERTESTS_H

#include <fstream>
#include <vector>
#include <lexer/Token.h>

#include "tests/TestBase.h"
#include "tools/Config.h"

/**
 * This class contains all tests for the lexer
 */
class LexerTests: public TestBase {
private:

    // ----- Attributes -----

    inline const static char *testFiles[] = {
            "/wol_scripts/1.0/lexer_test1.wol",
            "/wol_scripts/1.0/lexer_test2.wol",
            "/wol_scripts/1.0/lexer_test3.wol",
            "/wol_scripts/1.0/lexer_test4.wol",
            "/wol_scripts/1.0/lexer_test5.wol",
    };

    inline const static int expectedBahvior[] {
        SUCCESS,
        FAILURE,
        FAILURE,
        FAILURE,
        SUCCESS
    };

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
    int run() override;
};


#endif // CPP_WOL_LEXERTESTS_H
