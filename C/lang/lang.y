%{
#include <stdio.h>
#include <stdlib.h>
extern int linenum;
char *filename;
void yyerror(const char *string) {
    fprintf(stderr, "error in %s:%d: %s: %s", filename, linenum, string);
}

int main(void) {
    filename = "stdin";
    yyparse();
    return 0; 
}
%}

%token IMPORT FUN INT FLOAT STRING LBRACE RBRACE LPAREN RPAREN SEMICOLON QUOTE IDENT
%%

program:        imports {printf("Looking for imports in %s", $$);}// code | code
        ;
imports:        imports import {printf("MULTI IMPORT");}|;
import:         IMPORT IDENT
                {
                    printf("\tIMPORT STATEMENT\n");
                        }
        ;

code:           code funcdef | funcdef
        ;

funcdef:        FUN IDENT LPAREN RPAREN LBRACE stmts RBRACE {printf("found code\n");}
        ;

stmts:          INT SEMICOLON {printf("single statement\n");}| stmts INT SEMICOLON {printf("statements\n");}
        ;
