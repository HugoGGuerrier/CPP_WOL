#include "TestEngine.h"
#include "LexerTests.h"

// ----- Class methods -----

void TestEngine::init() {
    // Init the class vector
    TestEngine::testsToRun = new std::vector<TestBase>;

    // Add all test classes
    LexerTests lexerTests;
    TestEngine::testsToRun->emplace_back(lexerTests);

    // Set the init state to true
    TestEngine::isInit = true;
}

int TestEngine::run() {
    // Check that the engine is initialized
    if(!TestEngine::isInit) {
        TestEngine::init();
    }

    // Run the tests
    int res = 0;
    for(int i = 0; i < TestEngine::testsToRun->size(); i++) {
        res += TestEngine::testsToRun->operator[](i).run();
    }

    return res == 0 ? 0 : 1;
}