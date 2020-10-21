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
    unsigned int line;

    /**
     * The start position of the token in the line
     */
    unsigned int startPos;

    /**
     * The end position of the token in the line
     */
    unsigned int endPos;

    /**
     * The value of the token (used for identifiers, classes, attributes...)
     */
    const char *value;

    /**
     * The size of the token's value
     */
    unsigned int valueSize;

public:

    // ----- Constructors -----

    /**
     * Construct a new token with the wanted id
     *
     * @param id The token id
     */
    explicit Token();

    // ----- Destructor -----

    ~Token();

    // ----- Getters -----

    [[nodiscard]] int getId() const;

    [[nodiscard]] unsigned int getLine() const;

    [[nodiscard]] unsigned int getStartPos() const;

    [[nodiscard]] unsigned int getEndPos() const;

    [[nodiscard]] const char *getName() const;

    [[nodiscard]] const char *getValue() const;

    [[nodiscard]] unsigned int getValueSize() const;

    // ----- Setters -----

    void setId(int newId);

    void setLine(unsigned int line);

    void setStartPos(unsigned int startPos);

    void setEndPos(unsigned int endPos);

    void setValue(const char *value, unsigned int size);

    // ----- Class methods -----

    /**
     * Get the string representation of the token
     *
     * @return The string representation of the token
     */
    [[nodiscard]] std::string toString() const;
};

#endif // CPP_WOL_TOKEN_H
