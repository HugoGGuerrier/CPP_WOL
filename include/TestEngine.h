#ifndef CPP_WOL_TESTENGINE_H
#define CPP_WOL_TESTENGINE_H

#include <iostream>
#include <vector>

#include "TestBase.h"

/**
 * This class contains all methods to start all tests defined in the /tests directory
 */
class TestEngine {
private:

    // ----- Attributes -----

    /**
     * If the class has been initialized
     */
    inline static bool isInit = false;

    /**
     * All tests to run
     */
    static std::vector<TestBase> *testsToRun;

public:

    // ----- Class methods -----

    /**
     * Function to init the test engine
     */
    static void init();

    /**
     * Run the test engine
     *
     * @return The exit code of the tests
     */
    static int run();
};


#endif // CPP_WOL_TESTENGINE_H
