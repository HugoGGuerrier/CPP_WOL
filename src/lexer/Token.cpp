#include "lexer/Token.h"
#include "Lexenv.h"

// ----- Constructors -----

Token::Token() {
    this->id = -1;
    this->line = -1;
    this->startPos = -1;
    this->endPos = -1;
    this->value = nullptr;
    this->valueSize = 0;
}

// ----- Destructor -----

Token::~Token() {
    free((void *) this->value);
}

// ----- Getters -----

int Token::getId() const {
    return this->id;
}

unsigned int Token::getLine() const {
    return this->line;
}

unsigned int Token::getStartPos() const {
    return this->startPos;
}

unsigned int Token::getEndPos() const {
    return this->endPos;
}

const char *Token::getName() const {
    if(this->id != -1) {
        return Lexenv::nameArray[this->id];
    }
    return nullptr;
}

const char *Token::getValue() const {
    return this->value;
}

unsigned int Token::getValueSize() const {
    return this->valueSize;
}

// ----- Setters -----

void Token::setId(int newId) {
    this->id = newId;
}

void Token::setLine(unsigned int ln) {
    this->line = ln;
}

void Token::setStartPos(unsigned int sp) {
    this->startPos = sp;
}

void Token::setEndPos(unsigned int ep) {
    this->endPos = ep;
}

void Token::setValue(const char *v, unsigned int size) {
    this->value = v;
    this->valueSize = size;
}

// ----- Class methods -----

std::string Token::toString() const {
    std::string res = "[";
    res += this->id != -1 ? Lexenv::nameArray[this->id] : "ERROR";
    if(this->value != nullptr) {
        res += ":";
        res += std::string(this->value).substr(0, this->valueSize);
    }
    res += "]";
    return res;
}