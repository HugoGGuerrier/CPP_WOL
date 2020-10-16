#include "tests/TestBase.h"
#include "tools/Logger.h"

// ----- Internal methods -----

void TestBase::init(int number) {
    // Allocate the result
    this->testsStatus = static_cast<int *>( malloc(number * sizeof(int)) );
    this->testMessage = std::vector<std::string>(number);
    this->testStartTime = static_cast<clock_t *>( malloc(number * sizeof(clock_t)) );
    this->testEndTime = static_cast<clock_t *>( malloc(number * sizeof(clock_t)) );
    this->testNumber = number;

    // Fill the result with -1
    for(int i = 0; i < number; i++) {
        this->testsStatus[i] = -1;
    }
}

void TestBase::startTest(int index) {
    if(index <= this->testNumber && index > 0) {
        this->testStartTime[index - 1] = clock();
    }
}

void TestBase::succeedTest(int index, const std::string &message) {
    if(index <= this->testNumber && index > 0) {
        if(this->testsStatus[index - 1] == -1) {
            this->testsStatus[index - 1] = 0;
            this->testEndTime[index - 1] = clock();
            this->testMessage[index - 1] = message;
        } else {
            Logger::log_test_warn("Test " + std::to_string(index) + " already done...");
        }
    }
}

void TestBase::failTest(int index, const std::string &message) {
    if(index <= this->testNumber && index > 0) {
        if(this->testsStatus[index - 1] == -1) {
            this->testsStatus[index - 1] = 1;
            this->testEndTime[index - 1] = clock();
            this->testMessage[index - 1] = message;
        } else {
            Logger::log_test_warn("Test " + std::to_string(index) + " already done...");
        }
    }
}

int TestBase::verifyTests() {
    // Prepare the result
    int res = 0;

    // Verify each test
    for(int i = 0; i < this->testNumber; i++) {
        res += this->testsStatus[i];

        if(this->testsStatus[i] == 1 || this->testsStatus[i] == 0) {
            auto executionTime = ((double) this->testEndTime[i] - this->testStartTime[i]) / CLOCKS_PER_SEC;

            if(this->testsStatus[i] == 1) {
                Logger::log_test_failure("Test " + std::to_string(i + 1) + " : Failure ! (" + std::to_string(executionTime) + "s) | Message : " + this->testMessage[i]);
            } else {
                Logger::log_test_success("Test " + std::to_string(i + 1) + " : Success ! (" + std::to_string(executionTime) + "s) | Message : " + this->testMessage[i]);
            }
        } else {
            Logger::log_test_warn("Test " + std::to_string(i + 1) + " : Ignored !");
        }
    }

    // Return the result
    return res == 0 ? 0 : 1;
}

// ----- Destructor -----

TestBase::~TestBase() {
    free((void *) this->testsStatus);
    free((void *) this->testStartTime);
    free((void *) this->testEndTime);
}

// ----- Class methods -----

int TestBase::run() {
    Logger::log_err("Virtual method not override : TestBase::run()");

    return 1;
}
