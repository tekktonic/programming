LDFLAGS=-lfl
YACCFLAGS=-d
lang: y.tab.c lex.yy.c
	gcc y.tab.c lex.yy.c -o lang $(LDFLAGS)

y.tab.c: lang.y
	yacc -d lang.y
lex.yy.c: lang.l y.tab.h
	lex lang.l
