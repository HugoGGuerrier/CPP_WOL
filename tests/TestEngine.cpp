#include "TestEngine.h"
#include "LexerTests.h"

// ----- Class methods -----

int TestEngine::run() {
    // --- Run the tests
    int res = 0;

    // Lexer tests
    LexerTests lexerTests;
    res += TestEngine::runTest(lexerTests);

    // Return the exit code
    return res == 0 ? 0 : 1;
}

int TestEngine::runTest(const TestBase &testBase) {
    return testBase.run();
}
