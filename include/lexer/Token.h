#ifndef CPP_WOL_TOKEN_H
#define CPP_WOL_TOKEN_H

#include <iostream>

/**
 * This class represents a lexical token with all needed information about it
 */
class Token {
private:

    // ----- Attributes -----

    /**
     * The id of the current token
     */
    int id;

    /**
     * The line of the token in the lexed file
     */
    int line;

    /**
     * The start position of the token in the line
     */
    int startPos;

    /**
     * The end position of the token in the line
     */
    int endPos;

    /**
     * The value of the token (used for identifiers, classes, attributes...)
     */
    const char *value;

public:

    // ----- Constructors -----

    /**
     * Construct a new token with the wanted id
     *
     * @param id The token id
     */
    explicit Token(int id);

    /**
     * Construct a new empty token
     */
    Token() : Token(-1) {};

    // ----- Getters -----

    [[nodiscard]] int getId() const;

    [[nodiscard]] int getLine() const;

    [[nodiscard]] int getStartPos() const;

    [[nodiscard]] int getEndPos() const;

    [[nodiscard]] const char *getValue() const;

    [[nodiscard]] const char *getName() const;

    // ----- Setters -----

    void setId(int newId);

    void setLine(int line);

    void setStartPos(int startPos);

    void setEndPos(int endPos);

    void setValue(const char *value);
};

#endif // CPP_WOL_TOKEN_H
