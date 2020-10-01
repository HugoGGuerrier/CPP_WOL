#include "TestEngine.h"
#include "LexerTests.h"

// ----- Class methods -----

int TestEngine::run() {
    // --- Run the tests
    std::cout << std::endl;
    Logger::log_test_info("----- Start of the tests -----\n");

    int res = 0;

    // Lexer tests
    Logger::log_test_info("--- Run the Lexer tests");
    LexerTests lexerTests;
    res += lexerTests.run();

    std::cout << std::endl;
    Logger::log_test_info("----- End of the tests -----");

    // Return the exit code
    return res == 0 ? 0 : 1;
}
