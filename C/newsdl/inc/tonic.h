#ifndef TONIC_H
#define TONIC_H

#define json_check(obj, e) if (!obj) { fprintf(stderr, "%s:%d:%d %s\n", e.source, e.line, e.column, e.text); exit(1);}

typedef struct
{
    int x, y;
} Vect2;
typedef struct
{
    Vect2 pos;
    int w;
    int h;
} Rect;

#endif
