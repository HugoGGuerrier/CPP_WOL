#include "TestBase.h"
#include "Logger.h"

int TestBase::run() const {
    Logger::log_err("Virtual method not override : TestBase::run()");

    return 1;
}
