#ifndef CPP_WOL_LEXINGEXCEPTION_H
#define CPP_WOL_LEXINGEXCEPTION_H

#include <string>

#include "CustomBaseException.h"

class LexingException: public CustomBaseException {
public:
    LexingException(const std::string &cls, const std::string &func, const std::string &msg): CustomBaseException(cls, func, msg) {}
};

#endif // CPP_WOL_LEXINGEXCEPTION_H
