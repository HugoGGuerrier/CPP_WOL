#ifndef CPP_WOL_CUSTOMBASEEXCEPTION_H
#define CPP_WOL_CUSTOMBASEEXCEPTION_H

#include <exception>
#include <string>


/**
 * This is the base of all custom exceptions to avoid rewriting general behavior
 */
class CustomBaseException: public std::exception {
protected:

    /**
     * The class that the exception was risen in
     */
    std::string cls;

    /**
     * The function that rose exception
     */
    std::string func;

    /**
     * The exception message
     */
    std::string msg;

public:

    /**
     * Construct a new exception with the wanted message
     *
     * @param msg The error message
     */
    explicit CustomBaseException(const std::string &cls, const std::string &func, const std::string &msg) {
        this->cls = cls;
        this->func = func;
        this->msg = msg;
    }

    /**
     * Get the error message
     *
     * @return The error message
     */
    std::string what() {
        return this->cls + "::" +  this->func + " -> " + this->msg;
    }

    /**
     * Get the exception message
     *
     * @return The exception message in a string
     */
    std::string getMsg() {
        return this->msg;
    }
};

#endif // CPP_WOL_CUSTOMBASEEXCEPTION_H
