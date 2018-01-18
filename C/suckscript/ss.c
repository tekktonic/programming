#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

enum tokens {
	OPAREN,
	CPAREN,
	VAL
};

enum exitvals {
	FINE,
	TOKTYPE,
	VALTYPE,
	BADVAL
};

enum types {
	NUMBER,
	STRING,
	CHAR
};

struct value {
	enum types type;
	union {
		double number;
		char c;
		char *string;
	};
};

struct token {
	enum tokens toktype;
	struct value value;
};

struct tokenlist {
	struct token token;
	struct tokenlist *next;
};

void print_value(struct value *val)
{
	printf("<");
	switch(val->type) {
	case NUMBER:
		printf("number:%lf>\n", val->number);
		break;
	case CHAR:
		printf("char:%c>\n", val->c);
		break;
	case STRING:
		printf("string:%s>\n", val->string);
		break;
	default:
		fprintf(stderr, "Invalid value type! Only String, Number, and Char are implemented!\n");
		exit(VALTYPE);
	}
}
void print_token(struct token *tok)
{
	switch (tok->toktype) {
	case OPAREN:
		printf("OPAREN ");
		break;
	case CPAREN:
		printf("CPAREN ");
		break;
	case VAL:
		print_value(&(tok->value));
		break;
	default:
		fprintf(stderr, "Token has an invalid type!\n");
		exit(TOKTYPE);
	}
}
struct tokenlist *tokenize(char *string)
{
	char *tokstart = string;
	struct tokenlist *ret = calloc(1, sizeof(struct tokenlist));
	struct tokenlist *current = ret;

	for(;*string;string++) {
		if (!current) {
			current = 
		}
		if (isspace(*string)) {
			continue;
		}
		else if (*string == '"') {
			current->token.toktype = VAL;

			char *stringend = string+1;
			for(; *stringend; stringend++) {
				if (*stringend == '"')
					break;
			}
			if (!(*stringend)) {
				fprintf(stderr, "String never ends!\n");
				exit(BADVAL);
			}
			size_t string_length = stringend - string;
			current->token.value.type = STRING;
			current->token.value.string = calloc(string_length, sizeof(char));
			memcpy(current->token.value.string, string+1, string_length-1);
			string = stringend + 1;
		} else if (*string == '(') {
			current->token.toktype = OPAREN;
		}  else if (*string == ')') {
			current->token.toktype = CPAREN;
		}
		else if (isdigit(*string)) {
			current->token.toktype = VAL;
			current->token.
		}
	}

	return ret;
}

int main(void)
{
	struct tokenlist *tkl = tokenize("\"foobar\"");
	printf("%s\n", tkl->token.value.string);
}
