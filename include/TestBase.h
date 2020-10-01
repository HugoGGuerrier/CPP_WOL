#ifndef CPP_WOL_TESTBASE_H
#define CPP_WOL_TESTBASE_H

#include <vector>

#include "Logger.h"

/**
 * This is the base class of any test class
 */
class TestBase {
protected:

    // ----- Attributes -----

    /**
     * All tests status code
     */
    int *testsStatus;

    /**
     * The number of tests
     */
    int testNumber;

    // ----- Internal methods -----

    /**
     * Initialize the number of tests in the class
     *
     * @param number The number of tests
     */
    void init(int number);

    /**
     * Mark a test as success
     *
     * @param index The test to success
     */
    void succeedTest(int index);

    /**
     * Mark a test as failure
     *
     * @param index The test to fail
     */
    void failTest(int index);

    /**
     * Function to verify and display all the classes tests
     *
     * @return If all tests succeeded
     */
    int verifyTests();

public:

    // ----- Destructor -----

    ~TestBase();

    // ----- Class methods ------

    /**
     * The function to call when you have to run this test
     *
     * @return The exit code of the test
     */
    virtual int run();
};


#endif // CPP_WOL_TESTBASE_H
