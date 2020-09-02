# Init the project and the CMake version
project(cpp_wol)
cmake_minimum_required(VERSION 3.16)

# Set the cmake configuration
set(CMAKE_CXX_STANDARD 17)

# Set the compile variable
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(LEXER_DIR ${PROJECT_SOURCE_DIR}/src/lexer)
set(LEXENV_CREATOR_DIR ${LEXER_DIR}/lexenv_creator)

# Set the include directory
include_directories(include)

# Compile the lexical environment creator
add_executable(lexenv_creator ${LEXENV_CREATOR_DIR}/LexenvCreator.cpp)
set_target_properties(lexenv_creator PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LEXENV_CREATOR_DIR})

# Run the lexical environment creator
add_custom_command(OUTPUT "${LEXER_DIR}/Lexenv.cpp" COMMAND "${LEXENV_CREATOR_DIR}/lexenv_creator" ${LEXENV_CREATOR_DIR}/Lexenv.lex ${LEXER_DIR} DEPENDS ${LEXENV_CREATOR_DIR}/lexenv_creator ${LEXENV_CREATOR_DIR}/Lexenv.lex)
add_custom_target(generate_lexenv ALL DEPENDS ${LEXER_DIR}/Lexenv.cpp)

# Create the final executable, the WOL interpretor
add_executable(cpp_wol src/Main.cpp
        src/Config.cpp include/Config.h
        src/Logger.cpp include/Logger.h
        src/Utils.cpp include/Utils.h
        src/lexer/Lexenv.cpp src/lexer/Lexenv.h
        src/lexer/Lexer.cpp include/lexer/Lexer.h
        src/lexer/Token.cpp include/lexer/Token.h
        src/vm/VirtualMachine.cpp include/vm/VirtualMachine.h src/vm/Programs.cpp include/vm/Programs.h src/parser/ast/Program.cpp include/parser/ast/Program.h)
add_dependencies(cpp_wol generate_lexenv)
