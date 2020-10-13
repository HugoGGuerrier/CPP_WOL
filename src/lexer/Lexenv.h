#ifndef CPP_WOL_LEXENV_H
#define CPP_WOL_LEXENV_H

class Lexenv {
public:
	const static char *regexArray[];
	const static char *nameArray[];
	const static int symbolNumber = 46;

	const static int ONE_LINE_COMMENT = 0;
	const static int COMMENT_START = 1;
	const static int COMMENT_END = 2;
	const static int BLANK = 3;
	const static int SEMICOLON = 4;
	const static int DOUBLE_DOT = 5;
	const static int COMMA = 6;
	const static int DOT = 7;
	const static int EQ = 8;
	const static int EQEQ = 9;
	const static int PLUS = 10;
	const static int MINUS = 11;
	const static int TIMES = 12;
	const static int DIVIDE = 13;
	const static int LESS = 14;
	const static int MORE = 15;
	const static int LCURLY = 16;
	const static int RCURLY = 17;
	const static int LBRACKET = 18;
	const static int RBRACKET = 19;
	const static int LPAREN = 20;
	const static int RPAREN = 21;
	const static int CLASS = 22;
	const static int PRIVATE = 23;
	const static int PROTECTED = 24;
	const static int PUBLIC = 25;
	const static int PRINT_FUNC = 26;
	const static int VOID_TYPE = 27;
	const static int BOOL_TYPE = 28;
	const static int SHORT_TYPE = 29;
	const static int INT_TYPE = 30;
	const static int LONG_TYPE = 31;
	const static int FLOAT_TYPE = 32;
	const static int DOUBLE_TYPE = 33;
	const static int CHAR_TYPE = 34;
	const static int STRING_TYPE = 35;
	const static int ARRAY_TYPE = 36;
	const static int NODE_TYPE = 37;
	const static int INTERN_TYPE = 38;
	const static int TRUE_VAL = 39;
	const static int FALSE_VAL = 40;
	const static int NULL_VAL = 41;
	const static int NUMBER_VAL = 42;
	const static int IDENTIFIER = 43;
	const static int CHAR_VAL = 44;
	const static int STRING_VAL = 45;
};

#endif