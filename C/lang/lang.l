%{
#include "y.tab.h"
int linenum = 1;
%}
%%
import return IMPORT;
fun return FUN;

; return SEMICOLON;


[a-zA-Z][a-zA-Z_0-9] return IDENT;
\n {linenum++;}

. return (int)yytext[0];
