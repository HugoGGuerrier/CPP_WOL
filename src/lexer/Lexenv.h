#ifndef CPP_WOL_LEXENV_H
#define CPP_WOL_LEXENV_H

#include <regex.h>

class Lexenv {
public:
	const static char *nameArray[];

	const static int stopCharTable[];

	const static char *literalArray[];
	const static int literalCode[];

	const static char *regexArray[];
	const static int regexCode[];
	static regex_t regexTArray[];

	inline const static int symbolNumber = 49;
	inline const static int stopCharNumber = 24;
	inline const static int literalNumber = 23;
	inline const static int regexNumber = 5;

	inline const static int EOF_SYMBOL = 0;
	inline const static int BLANK = 1;
	inline const static int SEMICOLON = 2;
	inline const static int DOUBLE_DOT = 3;
	inline const static int COMMA = 4;
	inline const static int DOT = 5;
	inline const static int EQ = 6;
	inline const static int PLUS = 7;
	inline const static int MINUS = 8;
	inline const static int TIMES = 9;
	inline const static int DIVIDE = 10;
	inline const static int LESS = 11;
	inline const static int MORE = 12;
	inline const static int QUOTE = 13;
	inline const static int LCURLY = 14;
	inline const static int RCURLY = 15;
	inline const static int LBRACKET = 16;
	inline const static int RBRACKET = 17;
	inline const static int LPAREN = 18;
	inline const static int RPAREN = 19;
	inline const static int CLASS = 20;
	inline const static int PRIVATE = 21;
	inline const static int PROTECTED = 22;
	inline const static int PUBLIC = 23;
	inline const static int IF = 24;
	inline const static int ELSE = 25;
	inline const static int ELIF = 26;
	inline const static int PRIM_PRINT = 27;
	inline const static int PRIM_SIZE = 28;
	inline const static int VOID_TYPE = 29;
	inline const static int BOOL_TYPE = 30;
	inline const static int SHORT_TYPE = 31;
	inline const static int INT_TYPE = 32;
	inline const static int LONG_TYPE = 33;
	inline const static int FLOAT_TYPE = 34;
	inline const static int DOUBLE_TYPE = 35;
	inline const static int CHAR_TYPE = 36;
	inline const static int STRING_TYPE = 37;
	inline const static int ARRAY_TYPE = 38;
	inline const static int NODE_TYPE = 39;
	inline const static int INTERN_TYPE = 40;
	inline const static int TRUE_VAL = 41;
	inline const static int FALSE_VAL = 42;
	inline const static int NULL_VAL = 43;
	inline const static int INT_VAL = 44;
	inline const static int FLOAT_VAL = 45;
	inline const static int IDENTIFIER = 46;
	inline const static int CHAR_VAL = 47;
	inline const static int STRING_VAL = 48;

	static int getStopCharCode(char charToTest);
	static int getLexicalTokenCode(char *strToTest);
};

#endif