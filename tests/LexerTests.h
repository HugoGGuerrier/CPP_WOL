#ifndef CPP_WOL_LEXERTESTS_H
#define CPP_WOL_LEXERTESTS_H

#include <fstream>
#include <vector>
#include <lexer/Token.h>

#include "TestBase.h"
#include "Config.h"

/**
 * This class contains all tests for the lexer
 */
class LexerTests: public TestBase {
private:

    // ----- Attributes -----

    inline const static std::string testFile1 = Config::basePath + "/tests/wol_scripts/lexer_test1.wol";

    inline const static std::string testFile2 = Config::basePath + "/tests/wol_scripts/lexer_test2.wol";

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
