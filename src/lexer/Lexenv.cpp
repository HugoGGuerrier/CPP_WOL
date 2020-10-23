#include "Lexenv.h"

const char *Lexenv::nameArray[49] = {"EOF_SYMBOL", "BLANK", "SEMICOLON", "DOUBLE_DOT", "COMMA", "DOT", "EQ", "PLUS", "MINUS", "TIMES", "DIVIDE", "LESS", "MORE", "QUOTE", "LCURLY", "RCURLY", "LBRACKET", "RBRACKET", "LPAREN", "RPAREN", "CLASS", "PRIVATE", "PROTECTED", "PUBLIC", "IF", "ELSE", "ELIF", "PRIM_PRINT", "PRIM_SIZE", "VOID_TYPE", "BOOL_TYPE", "SHORT_TYPE", "INT_TYPE", "LONG_TYPE", "FLOAT_TYPE", "DOUBLE_TYPE", "CHAR_TYPE", "STRING_TYPE", "ARRAY_TYPE", "NODE_TYPE", "INTERN_TYPE", "TRUE_VAL", "FALSE_VAL", "NULL_VAL", "INT_VAL", "FLOAT_VAL", "IDENTIFIER", "CHAR_VAL", "STRING_VAL", };

const char Lexenv::stopCharArray[24] = {'\xFF', ' ', '\t', '\n', '\r', '\f', ';', ':', ',', '.', '=', '+', '-', '*', '/', '<', '>', '\"', '{', '}', '[', ']', '(', ')', };
const int Lexenv::stopCharCode[24] = {Lexenv::EOF_SYMBOL, Lexenv::BLANK, Lexenv::BLANK, Lexenv::BLANK, Lexenv::BLANK, Lexenv::BLANK, Lexenv::SEMICOLON, Lexenv::DOUBLE_DOT, Lexenv::COMMA, Lexenv::DOT, Lexenv::EQ, Lexenv::PLUS, Lexenv::MINUS, Lexenv::TIMES, Lexenv::DIVIDE, Lexenv::LESS, Lexenv::MORE, Lexenv::QUOTE, Lexenv::LCURLY, Lexenv::RCURLY, Lexenv::LBRACKET, Lexenv::RBRACKET, Lexenv::LPAREN, Lexenv::RPAREN, };

const char *Lexenv::regexArray[28] = {R"(^class$)", R"(^private$)", R"(^protected$)", R"(^public$)", R"(^if$)", R"(^else$)", R"(^elif$)", R"(^print$)", R"(^size$)", R"(^void$)", R"(^bool$)", R"(^short$)", R"(^int$)", R"(^long$)", R"(^float$)", R"(^double$)", R"(^char$)", R"(^string$)", R"(^array$)", R"(^node$)", R"(^intern$)", R"(^true$)", R"(^false$)", R"(^null|NULL$)", R"(^\-?[0-9]+$)", R"(^\-?[0-9]+\.[0-9]*$)", R"(^[a-zA-Z_][a-zA-Z0-9_]*$)", R"(^('\\?.')$)", };
const int Lexenv::regexCode[28] = {Lexenv::CLASS, Lexenv::PRIVATE, Lexenv::PROTECTED, Lexenv::PUBLIC, Lexenv::IF, Lexenv::ELSE, Lexenv::ELIF, Lexenv::PRIM_PRINT, Lexenv::PRIM_SIZE, Lexenv::VOID_TYPE, Lexenv::BOOL_TYPE, Lexenv::SHORT_TYPE, Lexenv::INT_TYPE, Lexenv::LONG_TYPE, Lexenv::FLOAT_TYPE, Lexenv::DOUBLE_TYPE, Lexenv::CHAR_TYPE, Lexenv::STRING_TYPE, Lexenv::ARRAY_TYPE, Lexenv::NODE_TYPE, Lexenv::INTERN_TYPE, Lexenv::TRUE_VAL, Lexenv::FALSE_VAL, Lexenv::NULL_VAL, Lexenv::INT_VAL, Lexenv::FLOAT_VAL, Lexenv::IDENTIFIER, Lexenv::CHAR_VAL, };

regex_t Lexenv::regexTArray[28];

int Lexenv::getStopCharCode(char charToTest) {
    for(int i = 0; i < Lexenv::stopCharNumber; i++) {
        if(charToTest == Lexenv::stopCharArray[i]) return Lexenv::stopCharCode[i];
    }
    return -1;
}

int Lexenv::getLexicalTokenCode(char *strToTest) {
    for(int i = 0; i < Lexenv::regexNumber; i++) {
        if(regexec(&Lexenv::regexTArray[i], strToTest, 0, nullptr, 0) == 0) return Lexenv::regexCode[i];
    }
    return -1;
}

