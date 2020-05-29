cmake_minimum_required(VERSION 3.16)
project(cpp_owl)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

add_executable(cpp_owl src/main.cpp include/Config.h src/Logger.cpp include/Logger.h src/Config.cpp include/Utils.h src/Utils.cpp)