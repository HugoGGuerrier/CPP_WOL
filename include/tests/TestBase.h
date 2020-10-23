#ifndef CPP_WOL_TESTBASE_H
#define CPP_WOL_TESTBASE_H

#include <vector>
#include <chrono>
#include <ctime>

#include "tools/Logger.h"

/**
 * This is the base class of any test class
 */
class TestBase {
protected:

    // ----- Attributes -----

    /**
     * The current test that is running
     */
    int currentTest;

    /**
     * All tests status code
     */
    int *testsStatus;

    /**
     * All test messages to display
     */
    std::vector<std::string> testMessage;

    /**
     * All tests start times
     */
    clock_t *testStartTime;

    /**
     * All test end times
     */
    clock_t *testEndTime;

    /**
     * The number of tests
     */
    int testNumber;

    /**
     * Test behavior codes
     */
    inline const static int SUCCESS = 1;
    inline const static int FAILURE = 2;

    // ----- Internal methods -----

    /**
     * Initialize the number of tests in the class
     *
     * @param number The number of tests
     */
    void init(int number);

    /**
     * Set the start time of a test to the current time
     *
     * @param index The test to start
     */
    void startTest(int index);

    /**
     * Mark a test as success
     *
     * @param index The test to success
     */
    void succeedTest(const std::string &message = "");

    /**
     * Mark a test as failure
     *
     * @param index The test to fail
     */
    void failTest(const std::string &message = "");

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
