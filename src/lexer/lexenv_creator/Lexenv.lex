-BLANK: \t\n\r\f

-SEMICOLON:;
-DOUBLE_DOT::
-COMMA:,
-DOT:.
-EQ:=
-PLUS:+
-MINUS:-
-TIMES:*
-DIVIDE:/
-LESS:<
-MORE:>
-QUOTE:\"

-LCURLY:{
-RCURLY:}
-LBRACKET:[
-RBRACKET:]
-LPAREN:(
-RPAREN:)

+CLASS:class
+PRIVATE:private
+PROTECTED:protected
+PUBLIC:public

+IF:if
+ELSE:else
+ELIF:elif

+PRIM_PRINT:print
+PRIM_SIZE:size

+VOID_TYPE:void
+BOOL_TYPE:bool
+SHORT_TYPE:short
+INT_TYPE:int
+LONG_TYPE:long
+FLOAT_TYPE:float
+DOUBLE_TYPE:double
+CHAR_TYPE:char
+STRING_TYPE:string
+ARRAY_TYPE:array
+NODE_TYPE:node
+INTERN_TYPE:intern

+TRUE_VAL:true
+FALSE_VAL:false

NULL_VAL:null|NULL

INT_VAL:\-?[0-9]+
FLOAT_VAL:\-?[0-9]+\.[0-9]*
IDENTIFIER:[a-zA-Z_][a-zA-Z0-9_]*
CHAR_VAL:('\\?.')

~STRING_VAL