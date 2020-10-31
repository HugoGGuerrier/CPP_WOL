#ifndef CPP_WOL_ENCODINGS_H
#define CPP_WOL_ENCODINGS_H

/**
 * This class contains all functions to support multiple encoding format
 */
class Encodings {
public:

    /**
     * Get the utf-8 translation from utf-16
     *
     * @param c The utf-16 char
     * @return The utf-8 char
     */
    static char utf16(char16_t c);
};


#endif // CPP_WOL_ENCODINGS_H
