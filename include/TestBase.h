#ifndef CPP_WOL_TESTBASE_H
#define CPP_WOL_TESTBASE_H

#include "Logger.h"

/**
 * This is the base class of any test class
 */
class TestBase {
public:

    /**
     * The function to call when you have to run this test
     *
     * @return The exit code of the test
     */
    [[nodiscard]] virtual int run() const;
};


#endif // CPP_WOL_TESTBASE_H
