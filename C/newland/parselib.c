#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parselib.h"

bool is_delimiter(char c)
{
    return (isspace(c)) || c == 0;// || c == '(' || c == ')')
}

bool is_balanced(const char *str)
{
    if (*str++ != '(')
    {
        return true; // if it's not a list, it's balanced
    }

    int unbalanced_parens = 1;

    while (unbalanced_parens > 0)
    {
        if (*str == '\0')
            return false;
        if (*str == ')')
            unbalanced_parens--;

        str++;
    }

    return true;
}
struct value read_int(const char *str, bool *errored)
{
    int value = 0;
    while(isdigit(*str))
    {
        value *= 10;
        value += (*str) - 0x30; // ascii digit to value
        str++;
    }
    if (!is_delimiter(*str))
    {
        *errored = true;
        return new_unknown_value();
    }
    
    return new_int_value(value);
}

struct value read_double(const char *str, bool *errored)
{
    double denominator = 10.0;
    
    double value = 0.0;
    bool is_negative = false;

    if (*str == '-')
    {
        is_negative = true;
        str++;
    }
    
    while(isdigit(*str))
    {
        value *= 10;
        value += (*str) - 0x30; // ascii/utf8 digit to value
        str++;
    }
    
    if (*(str++) != '.')
    {
        *errored = true;
        return new_unknown_value();
    }
    
    while(isdigit(*str))
    {
        value += ((*str) - 0x30) / denominator; // ascii digit to value, divided to
        // make it act fractional
        denominator *= 10; // move onto next fractional digit
        str++;
    }
    
    if (!is_delimiter(*str))
    {
        *errored = true;
        return new_unknown_value();
    }
    
    printf("literal double %lf\n", value);
    return new_double_value(value);

}

bool parse_as_int(const char *str)
{
    const char *current = str;
    while(isdigit(*current)) {current++;}
    if (*current == '.')
    {
        return false;
    }
    else
    {
        return true;
    }
}

struct value read_char(const char *str, bool *errored)
{
    if (*str++ == '#')
    {
        printf("CHARACTER %c %d", *str, *(str+1));
        if (isprint(*str))
        {
            if (is_delimiter(*(str+1)))
            {
                return new_char_value(*str);
            }
        }
    }
    *errored = true;
    return new_unknown_value();
}

struct value read_string(const char *str, bool *errored)
{
    const char *start;
    char *tmp;
    int length;
    if (*str++ == '"')
    {
        start = str;
    }
    else
    {
        *errored = true;
        return new_unknown_value();
    }

    while (*str != '"')
    {
        if (*str == '\n')
        {
            printf("Unmatched \"\n");
            *errored = true;
            return new_unknown_value();
        }
        str++;
    }

    length = str - start;
    printf("STRING LENGTH %d\n", length);    
    tmp = malloc(length + 1);
    snprintf(tmp, length + 1, "%s", start);
    struct value ret = new_string_value(tmp);
    printf("RET LENGTH: %ld, %s", strlen(ret.value.s), tmp);
    free(tmp);
    return ret;
}

struct value read_nil(const char *str, bool *errored)
{
    
    if (*str == '_' && is_delimiter(*(str+1)))
        return new_nil_value();
    *errored = true;
    return new_unknown_value();
}


struct value read_value(const char *str)
{
    const char *current = str;
    bool errored = false;
    struct value ret;
    enum value_type parsed_as;
    
    while(is_delimiter(*current)) {current++;} // chomp any starting nonsense
    if (*current == '#')
    {
        printf("PARSING AS CHAR\n");
        parsed_as = VAL_CHAR;
        ret = read_char(current, &errored);
        if (errored)
            goto error_state;
    }
    else if (*current == '"')
    {
        printf("PARSING AS STRING\n");
        parsed_as = VAL_STRING;
        ret = read_string(current, &errored);
        if (errored)
            goto error_state;
    }
    else if (*current == '_')
    {
        printf("PARSING AS NIL\n");
        parsed_as = VAL_NIL;
        ret = read_nil(current, &errored);
        if (errored)
            goto error_state;        
    }
    else if (isdigit(*current))
    {
        if (parse_as_int(current))
        {
            printf("PARSING AS INT\n");
            parsed_as = VAL_INT;
            ret = read_int(current, &errored);
        }
        else
        {
            printf("PARSING AS DOUBLE\n");
            parsed_as = VAL_DOUBLE;
            ret = read_double(current, &errored);
        }
        if (errored)
            goto error_state;        
    }
    
    else if (*current == '(')
    {
        printf("PARSING AS FUNCTION\n");
        if (!is_balanced(current))
        {
            printf("Unbalanced parens in %s", current);
            goto error_state;
        }
        parsed_as = VAL_FUNC;
        ret = read_nil(current, &errored);
        if (errored)
            goto error_state;        
    }
    else
    {
        parsed_as = VAL_UNKNOWN;
        ret = new_unknown_value();
        goto error_state;
    }

    
    return ret;
    
error_state:
    fprintf(stderr, "Unable to parse %s, looked like a %s\n", current, type_strings[parsed_as]);
    return ret;
}
