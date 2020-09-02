#include "lexer/Token.h"
#include "Lexenv.h"

// ----- Constructors -----

Token::Token(int id) {
    this->id = id;
    this->line = -1;
    this->startPos = -1;
    this->endPos = -1;
    this->value = std::string();
}

// ----- Getters -----

int Token::getId() const {
    return this->id;
}

int Token::getLine() const {
    return this->line;
}

int Token::getStartPos() const {
    return this->startPos;
}

int Token::getEndPos() const {
    return this->endPos;
}

std::string Token::getValue() const {
    return this->value;
}

// ----- Setters -----

void Token::setId(int newId) {
    this->id = newId;
}

void Token::setLine(int ln) {
    this->line = ln;
}

void Token::setStartPos(int sp) {
    this->startPos = sp;
}

void Token::setEndPos(int ep) {
    this->endPos = ep;
}

void Token::setValue(const std::string &v) {
    this->value = v;
}

// ----- Class methods -----

std::string Token::toString() const {
    std::string res;
    res = Lexenv::nameArray[this->id];

    if(!this->value.empty()) {
        res += "=" + this->value;
    }

    return res;
}