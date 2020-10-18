#ifndef CPP_WOL_BOOTSTRAPEXCEPTION_H
#define CPP_WOL_BOOTSTRAPEXCEPTION_H

#include "CustomBaseException.h"

class BootstrapException: public CustomBaseException {
public:
    BootstrapException(const std::string &cls, const std::string &func, const std::string &msg): CustomBaseException(cls, func, msg) {}
};

#endif // CPP_WOL_BOOTSTRAPEXCEPTION_H
