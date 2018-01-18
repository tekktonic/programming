#ifndef T_GLOBAL
#define T_GLOBAL

typedef void (*freefunc)(void*);
typedef enum t_err
{
    T_ERR_OK = 0,
    T_ERR_NOMEM = -1,
    T_ERR_NOELM = -2,
} t_err;
#endif
