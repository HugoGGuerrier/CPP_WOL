#include "tools/Encodings.h"

char Encodings::utf16(char16_t c) {
    return c >> 8 == 0 ? (char)c : '\0';
}