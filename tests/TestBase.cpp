#include "TestBase.h"
#include "Logger.h"

// ----- Internal methods -----

void TestBase::init(int number) {
    // Allocate the result
    this->testsStatus = static_cast<int *>( malloc(number * sizeof(int)) );
    this->testMessage = static_cast<std::string *>( malloc(number * sizeof(std::string)) );
    this->testStartTime = static_cast<std::chrono::time_point<std::chrono::system_clock> *>( malloc(number * sizeof(std::chrono::time_point<std::chrono::system_clock>)) );
    this->testEndTime = static_cast<std::chrono::time_point<std::chrono::system_clock> *>( malloc(number * sizeof(std::chrono::time_point<std::chrono::system_clock>)) );
    this->testNumber = number;

    // Fill the result with -1
    for(int i = 0; i < number; i++) {
        this->testsStatus[i] = -1;
    }
}

void TestBase::succeedTest(int index, const std::string &message) {
    if(this->testsStatus[index - 1] == -1) {
        this->testsStatus[index - 1] = 0;
    } else {
        Logger::log_test_warn("Test " + std::to_string(index) + " already done...");
    }
}

void TestBase::failTest(int index, const std::string &message) {
    if(this->testsStatus[index - 1] == -1) {
        this->testsStatus[index - 1] = 1;
    } else {
        Logger::log_test_warn("Test " + std::to_string(index) + " already done...");
    }
}

int TestBase::verifyTests() {
    // Prepare the result
    int res = 0;

    // Verify each test
    for(int i = 0; i < this->testNumber; i++) {
        res += this->testsStatus[i];
        if(this->testsStatus[i] == 1) {
            Logger::log_test_failure("Test " + std::to_string(i + 1) + " : Failure !");
        } else if(this->testsStatus[i] == 0) {
            Logger::log_test_success("Test " + std::to_string(i + 1) + " : Success !");
        } else if(this->testsStatus[i] == -1) {
            Logger::log_test_warn("Test " + std::to_string(i + 1) + " : Ignored !");
        }
    }

    // Return the result
    return res == 0 ? 0 : 1;
}

// ----- Destructor -----

TestBase::~TestBase() {
    free((void *) this->testsStatus);
    free((void *) this->testMessage);
    free((void *) this->testStartTime);
    free((void *) this->testEndTime);
}

// ----- Class methods -----

int TestBase::run() {
    Logger::log_err("Virtual method not override : TestBase::run()");

    return 1;
}
