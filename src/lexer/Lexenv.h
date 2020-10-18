#ifndef CPP_WOL_LEXENV_H
#define CPP_WOL_LEXENV_H

#include <regex.h>

class Lexenv {
public:
	const static char *nameArray[];

	const static char stopCharArray[];
	const static int stopCharCode[];

	const static char *regexArray[];
	const static int regexCode[];
	static regex_t regexTArray[];

	inline const static int symbolNumber = 42;
	inline const static int stopCharNumber = 18;
	inline const static int regexNumber = 24;

	inline const static int BLANK = 0;
	inline const static int SEMICOLON = 1;
	inline const static int DOUBLE_DOT = 2;
	inline const static int COMMA = 3;
	inline const static int DOT = 4;
	inline const static int EQ = 5;
	inline const static int PLUS = 6;
	inline const static int MINUS = 7;
	inline const static int TIMES = 8;
	inline const static int DIVIDE = 9;
	inline const static int LESS = 10;
	inline const static int MORE = 11;
	inline const static int LCURLY = 12;
	inline const static int RCURLY = 13;
	inline const static int LBRACKET = 14;
	inline const static int RBRACKET = 15;
	inline const static int LPAREN = 16;
	inline const static int RPAREN = 17;
	inline const static int CLASS = 18;
	inline const static int PRIVATE = 19;
	inline const static int PROTECTED = 20;
	inline const static int PUBLIC = 21;
	inline const static int PRINT_FUNC = 22;
	inline const static int VOID_TYPE = 23;
	inline const static int BOOL_TYPE = 24;
	inline const static int SHORT_TYPE = 25;
	inline const static int INT_TYPE = 26;
	inline const static int LONG_TYPE = 27;
	inline const static int FLOAT_TYPE = 28;
	inline const static int DOUBLE_TYPE = 29;
	inline const static int CHAR_TYPE = 30;
	inline const static int STRING_TYPE = 31;
	inline const static int ARRAY_TYPE = 32;
	inline const static int NODE_TYPE = 33;
	inline const static int INTERN_TYPE = 34;
	inline const static int TRUE_VAL = 35;
	inline const static int FALSE_VAL = 36;
	inline const static int NULL_VAL = 37;
	inline const static int NUMBER_VAL = 38;
	inline const static int IDENTIFIER = 39;
	inline const static int CHAR_VAL = 40;
	inline const static int STRING_VAL = 41;
};

#endif