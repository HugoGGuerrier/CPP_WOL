#ifndef CPP_WOL_FILEEXCEPTION_H
#define CPP_WOL_FILEEXCEPTION_H

#include <string>

#include "CustomBaseException.h"

class FileException: public CustomBaseException {
public:
    FileException(const std::string &cls, const std::string &func, const std::string &msg): CustomBaseException(cls, func, msg) {}
};

#endif // CPP_WOL_FILEEXCEPTION_H
