#ifndef CPP_WOL_UTILS_H
#define CPP_WOL_UTILS_H

#define EOF_CHAR '\xFF'

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

/**
 * Get the escaped character code in an int, this function define all known escaped chars
 *
 * @param charToEscape The char to escape
 * @return The char escaped code, -1 else
 */
int getEscapedChar(char charToEscape);

/**
 * Display a vector of token
 *
 * @param vec The vector to display
 */
std::string vectos(const std::vector<Token> &vec, bool nl = false);


#endif // CPP_WOL_UTILS_H
