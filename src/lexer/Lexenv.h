#ifndef CPP_WOL_LEXENV_H
#define CPP_WOL_LEXENV_H

class Lexenv {
public:
	const static char *regexArray[];
	const static char *nameArray[];
	const static int ONE_LINE_COMMENT = 0;
	const static int COMMENT_START = 1;
	const static int COMMENT_END = 2;
	const static int SEMICOLON = 3;
	const static int COMMA = 4;
	const static int DOT = 5;
	const static int EQ = 6;
	const static int EQEQ = 7;
	const static int PLUS = 8;
	const static int MINUS = 9;
	const static int LESS = 10;
	const static int MORE = 11;
	const static int LCURLY = 12;
	const static int RCURLY = 13;
	const static int LBRACKET = 14;
	const static int RBRACKET = 15;
	const static int LPAREN = 16;
	const static int RPAREN = 17;
	const static int GLOBAL = 18;
	const static int CLASS = 19;
	const static int STATIC = 20;
	const static int PRIVATE = 21;
	const static int PROTECTED = 22;
	const static int PUBLIC = 23;
	const static int PRINT_FUNC = 24;
	const static int BOOL_TYPE = 25;
	const static int SHORT_TYPE = 26;
	const static int INT_TYPE = 27;
	const static int LONG_TYPE = 28;
	const static int FLOAT_TYPE = 29;
	const static int DOUBLE_TYPE = 30;
	const static int CHAR_TYPE = 31;
	const static int STRING_TYPE = 32;
	const static int ARRAY_TYPE = 33;
	const static int NODE_TYPE = 34;
	const static int INTERN_TYPE = 35;
	const static int IDENTIFIER = 36;
	const static int TRUE_VAL = 37;
	const static int FALSE_VAL = 38;
	const static int NULL_VAL = 39;
	const static int NUMBER_VAL = 40;
	const static int CHAR_VALUE = 41;
	const static int STRING_VALUE = 42;
};

#endif