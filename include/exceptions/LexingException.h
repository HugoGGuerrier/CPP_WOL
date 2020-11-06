#ifndef CPP_WOL_LEXINGEXCEPTION_H
#define CPP_WOL_LEXINGEXCEPTION_H

#include <string>

#include "CustomBaseException.h"

class LexingException: public CustomBaseException {
public:
    LexingException(const std::string &msg): CustomBaseException("Lexer", "doLexInOnce", msg) {}
};

#endif // CPP_WOL_LEXINGEXCEPTION_H
