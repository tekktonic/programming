#ifndef STAS_TYPES_H
#define STAS_TYPES_H
typedef enum
{
    NUM,
    STR,
    FUNC,
    LIT,
    BOOL,
    CONS,
    NIL,
    SYM,
    PRIM, // primitive function
}Type;
#endif
