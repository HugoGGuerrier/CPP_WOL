#include <cstring>

#include "Lexenv.h"

const char *Lexenv::nameArray[49] = {"EOF_SYMBOL", "BLANK", "SEMICOLON", "DOUBLE_DOT", "COMMA", "DOT", "EQ", "PLUS", "MINUS", "TIMES", "DIVIDE", "LESS", "MORE", "QUOTE", "LCURLY", "RCURLY", "LBRACKET", "RBRACKET", "LPAREN", "RPAREN", "CLASS", "PRIVATE", "PROTECTED", "PUBLIC", "IF", "ELSE", "ELIF", "PRIM_PRINT", "PRIM_SIZE", "VOID_TYPE", "BOOL_TYPE", "SHORT_TYPE", "INT_TYPE", "LONG_TYPE", "FLOAT_TYPE", "DOUBLE_TYPE", "CHAR_TYPE", "STRING_TYPE", "ARRAY_TYPE", "NODE_TYPE", "INTERN_TYPE", "TRUE_VAL", "FALSE_VAL", "NULL_VAL", "INT_VAL", "FLOAT_VAL", "IDENTIFIER", "CHAR_VAL", "STRING_VAL", };

const int Lexenv::stopCharTable[256] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, Lexenv::BLANK, Lexenv::BLANK, -1, Lexenv::BLANK, Lexenv::BLANK, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, Lexenv::BLANK, -1, Lexenv::QUOTE, -1, -1, -1, -1, -1, Lexenv::LPAREN, Lexenv::RPAREN, Lexenv::TIMES, Lexenv::PLUS, Lexenv::COMMA, Lexenv::MINUS, Lexenv::DOT, Lexenv::DIVIDE, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, Lexenv::DOUBLE_DOT, Lexenv::SEMICOLON, Lexenv::LESS, Lexenv::EQ, Lexenv::MORE, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, Lexenv::LBRACKET, -1, Lexenv::RBRACKET, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, Lexenv::LCURLY, -1, Lexenv::RCURLY, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, Lexenv::EOF_SYMBOL, };

const char *Lexenv::literalArray[23] = {"class", "private", "protected", "public", "if", "else", "elif", "print", "size", "void", "bool", "short", "int", "long", "float", "double", "char", "string", "array", "node", "intern", "true", "false", };
const int Lexenv::literalCode[23] = {Lexenv::CLASS, Lexenv::PRIVATE, Lexenv::PROTECTED, Lexenv::PUBLIC, Lexenv::IF, Lexenv::ELSE, Lexenv::ELIF, Lexenv::PRIM_PRINT, Lexenv::PRIM_SIZE, Lexenv::VOID_TYPE, Lexenv::BOOL_TYPE, Lexenv::SHORT_TYPE, Lexenv::INT_TYPE, Lexenv::LONG_TYPE, Lexenv::FLOAT_TYPE, Lexenv::DOUBLE_TYPE, Lexenv::CHAR_TYPE, Lexenv::STRING_TYPE, Lexenv::ARRAY_TYPE, Lexenv::NODE_TYPE, Lexenv::INTERN_TYPE, Lexenv::TRUE_VAL, Lexenv::FALSE_VAL, };

const char *Lexenv::regexArray[5] = {R"(^null|NULL$)", R"(^\-?[0-9]+$)", R"(^\-?[0-9]+\.[0-9]*$)", R"(^[a-zA-Z_][a-zA-Z0-9_]*$)", R"(^('\\?.')$)", };
const int Lexenv::regexCode[5] = {Lexenv::NULL_VAL, Lexenv::INT_VAL, Lexenv::FLOAT_VAL, Lexenv::IDENTIFIER, Lexenv::CHAR_VAL, };

regex_t Lexenv::regexTArray[5];

int Lexenv::getStopCharCode(char charToTest) {
    return Lexenv::stopCharTable[(unsigned char)charToTest];
}

int Lexenv::getLexicalTokenCode(char *strToTest) {
    for(int i = 0; i < Lexenv::literalNumber; i++) {
        if(strcmp(strToTest, Lexenv::literalArray[i]) == 0) return Lexenv::literalCode[i];
    }
    for(int i = 0; i < Lexenv::regexNumber; i++) {
        if(regexec(&Lexenv::regexTArray[i], strToTest, 0, nullptr, 0) == 0) return Lexenv::regexCode[i];
    }
    return -1;
}

