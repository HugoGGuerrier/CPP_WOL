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
	const static int DOUBLE_DOT = 4;
	const static int COMMA = 5;
	const static int DOT = 6;
	const static int EQ = 7;
	const static int EQEQ = 8;
	const static int PLUS = 9;
	const static int MINUS = 10;
	const static int LESS = 11;
	const static int MORE = 12;
	const static int LCURLY = 13;
	const static int RCURLY = 14;
	const static int LBRACKET = 15;
	const static int RBRACKET = 16;
	const static int LPAREN = 17;
	const static int RPAREN = 18;
	const static int CLASS = 19;
	const static int PRIVATE = 20;
	const static int PROTECTED = 21;
	const static int PUBLIC = 22;
	const static int PRINT_FUNC = 23;
	const static int BOOL_TYPE = 24;
	const static int SHORT_TYPE = 25;
	const static int INT_TYPE = 26;
	const static int LONG_TYPE = 27;
	const static int FLOAT_TYPE = 28;
	const static int DOUBLE_TYPE = 29;
	const static int CHAR_TYPE = 30;
	const static int STRING_TYPE = 31;
	const static int ARRAY_TYPE = 32;
	const static int NODE_TYPE = 33;
	const static int INTERN_TYPE = 34;
	const static int IDENTIFIER = 35;
	const static int TRUE_VAL = 36;
	const static int FALSE_VAL = 37;
	const static int NULL_VAL = 38;
	const static int NUMBER_VAL = 39;
	const static int CHAR_VAL = 40;
	const static int STRING_VAL = 41;
};

#endif