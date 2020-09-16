#include "Lexenv.h"

const char *Lexenv::nameArray[43] = {"ONE_LINE_COMMENT", "COMMENT_START", "COMMENT_END", "SEMICOLON", "DOUBLE_DOT", "COMMA", "DOT", "EQ", "EQEQ", "PLUS", "MINUS", "LESS", "MORE", "LCURLY", "RCURLY", "LBRACKET", "RBRACKET", "LPAREN", "RPAREN", "CLASS", "PRIVATE", "PROTECTED", "PUBLIC", "PRINT_FUNC", "VOID_TYPE", "BOOL_TYPE", "SHORT_TYPE", "INT_TYPE", "LONG_TYPE", "FLOAT_TYPE", "DOUBLE_TYPE", "CHAR_TYPE", "STRING_TYPE", "ARRAY_TYPE", "NODE_TYPE", "INTERN_TYPE", "IDENTIFIER", "TRUE_VAL", "FALSE_VAL", "NULL_VAL", "NUMBER_VAL", "CHAR_VAL", "STRING_VAL"};
const char *Lexenv::regexArray[43] = {R"(\/\/.*\R)", R"(\/\*)", R"(\*\/)", R"([;])", R"([:])", R"([,])", R"([\.])", R"([=])", R"(==)", R"([\+])", R"([\-])", R"([\<])", R"([\>])", R"([{])", R"([}])", R"([\[])", R"([\]])", R"([(])", R"([)])", R"(class)", R"(private)", R"(protected)", R"(public)", R"(print)", R"(void)", R"(bool)", R"(short)", R"(int)", R"(long)", R"(float)", R"(double)", R"(char)", R"(string)", R"(array)", R"(node)", R"(intern)", R"([a-zA-Z_][a-zA-Z0-9_]*)", R"(true)", R"(false)", R"(null|NULL)", R"(\-?[0-9]+(\.?[0-9])?[0-9]*)", R"(\'.\')", R"(\".*\")"};
