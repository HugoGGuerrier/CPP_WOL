#ifndef CPP_WOL_TESTENGINE_H
#define CPP_WOL_TESTENGINE_H

#include <iostream>
#include <vector>

#include "TestBase.h"

/**
 * This class contains all methods to start all tests defined in the /tests directory
 */
class TestEngine {
public:

    // ----- Class methods -----

    /**
     * Run the test engine
     *
     * @return The exit code of the tests
     */
    static int run();
};


#endif // CPP_WOL_TESTENGINE_H
