%{
#include "y.tab.h"
int linenum;
%}
%%
[ \t] ;// chomp whitespace
[0-9]+\.[0-9]* {yylval.f = atof(yytext); return DOUBLE;}
[0-9]+ {yylval.i = atoi(yytext); return INT;}
\".*\" {yylval.s = strdup(yytext); return STRING;}
\n {++linenum;}
%%

