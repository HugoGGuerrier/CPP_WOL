#ifndef CPP_WOL_UTILS_H
#define CPP_WOL_UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <lexer/Token.h>

/**
 * Get the string representation of a boolean
 *
 * @param b The boolean
 * @return The string representing the boolean
 */
std::string btos(bool b);

/**
 * Get if a file exists and is readable
 *
 * @param file The file to verify
 * @return True if the file is readable
 */
bool fileExists(const std::string &file);

// ----- Vector displaying functions -----

/**
 * Display a vector
 *
 * @param vector The vector to display
 * @param newLine If you want to make a new line at each element
 * @return The string representation of the vector
 */
std::string vectos(const std::vector<std::string> &vector, bool newLine);

#endif // CPP_WOL_UTILS_H
