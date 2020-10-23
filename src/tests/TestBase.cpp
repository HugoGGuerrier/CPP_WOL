#include "tests/TestBase.h"
#include "tools/Logger.h"

// ----- Internal methods -----

void TestBase::init(int number) {
    // Allocate the result
    this->testsStatus = static_cast<int *>( malloc(number * sizeof(int)) );
    this->testMessage = std::vector<std::string>(number);
    this->testStartTime = static_cast<clock_t *>( malloc(number * sizeof(clock_t)) );
    this->testEndTime = static_cast<clock_t *>( malloc(number * sizeof(clock_t)) );
    this->currentTest = 0;
    this->testNumber = number;

    // Fill the result with -1
    for(int i = 0; i < number; i++) {
        this->testsStatus[i] = -1;
    }
}

void TestBase::startTest(int index) {
    // Start the wanted test
    if(index < this->testNumber && index >= 0) {
        this->testStartTime[index] = clock();
        this->currentTest = index;
    }
}

void TestBase::succeedTest(const std::string &message) {
    // Succeed the wanted test and get the execution time
    if(this->currentTest < this->testNumber && this->currentTest >= 0) {
        if(this->testsStatus[this->currentTest] == -1) {
            this->testsStatus[this->currentTest] = 0;
            this->testEndTime[this->currentTest] = clock();
            this->testMessage[this->currentTest] = message;
        } else {
            Logger::log_test_warn("Test " + std::to_string(this->currentTest) + " already done...");
        }
    }
}

void TestBase::failTest(const std::string &message) {
    // Fail the wanted test and get the execution time
    if(this->currentTest < this->testNumber && this->currentTest >= 0) {
        if(this->testsStatus[this->currentTest] == -1) {
            this->testsStatus[this->currentTest] = 1;
            this->testEndTime[this->currentTest] = clock();
            this->testMessage[this->currentTest] = message;
        } else {
            Logger::log_test_warn("Test " + std::to_string(this->currentTest) + " already done...");
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
    // Free all allocated memory
    free((void *) this->testsStatus);
    free((void *) this->testStartTime);
    free((void *) this->testEndTime);
}

// ----- Class methods -----

int TestBase::run() {
    Logger::log_err("Virtual method not override : TestBase::run()");

    return 1;
}
