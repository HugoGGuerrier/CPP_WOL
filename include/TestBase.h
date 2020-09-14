#ifndef CPP_WOL_TESTBASE_H
#define CPP_WOL_TESTBASE_H


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
    virtual int run();

};

int TestBase::run() {
    Logger::log_warn("Override this method! (TestBase::run())");

    return 1;
}


#endif // CPP_WOL_TESTBASE_H
