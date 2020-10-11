#include <regex>
#include <cstdio>
#include <cstdlib>

#include "lexer/Lexer.h"
#include "Lexenv.h"

#include "exceptions/FileException.h"
#include "exceptions/LexingException.h"

// ----- Static fields -----

const char *Lexer::stopString[17] = {
        ";",
        ":",
        ",",
        ".",
        "=",
        "+",
        "-",
        "*",
        "/",
        "<",
        ">",
        "{",
        "}",
        "[",
        "]",
        "(",
        ")"
};

const int Lexer::stopCodes[17] = {
        Lexenv::SEMICOLON,
        Lexenv::DOUBLE_DOT,
        Lexenv::COMMA,
        Lexenv::DOT,
        Lexenv::EQ,
        Lexenv::PLUS,
        Lexenv::MINUS,
        Lexenv::TIMES,
        Lexenv::DIVIDE,
        Lexenv::LESS,
        Lexenv::MORE,
        Lexenv::LCURLY,
        Lexenv::RCURLY,
        Lexenv::LBRACKET,
        Lexenv::RBRACKET,
        Lexenv::LPAREN,
        Lexenv::RPAREN
};

// ----- Constructors -----

Lexer::Lexer(const std::string &file) {
    this->file = file;
}

// ----- Internal methods -----

void Lexer::addToken(int tokenId, int startPos, int endPos, int line, const char *value) {
    auto newToken = std::make_unique<Token>(Token(tokenId));
    newToken->setStartPos(startPos);
    newToken->setEndPos(endPos);
    newToken->setLine(line);
    newToken->setValue(value);
    this->lexResult.emplace_back();
}

// ----- Getters -----

void Lexer::getLexResult(std::vector<Token> &result) const {
    // Clear the result vector
    result.clear();

    // Copy all tokens in the result vector
    result = this->lexResult;
}

// ----- Class methods -----

void Lexer::doLex() {
    // Verify if the file was already lexed
    if(this->lexResult.empty()) {

        // Open the file to lex
        FILE *fileToLex;
        fopen(this->file.c_str(), "r");

        fileToLex.open(this->file);

        // Verify the file
        if(!fileToLex.is_open()) {
            throw FileException("Lexer", "doLex", "File " + this->file + " is missing or unreadable. Cannot continue lexing.");
        }

        // Get the full code

        // TODO : Use low level function fopen() to read the file char by char

        // TODO : Do the lexing process and store it into the lexing result

        // Close the file
        fileToLex.close();

    }
}
