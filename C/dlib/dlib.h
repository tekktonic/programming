#ifndef DLIB_H
#define DLIB_H
#include "dvalue.h"
#include "dlist.h"
#include "dhashtable.h"
#include "dvector.h"



/*#define DINIT_STRUCT(ptr, typ, ...) do{if(ptr == NULL){ptr = malloc(sizeof(typ));}DNULLCROAK(ptr, "Can't init struct of " #typ)*(typ*)ptr = (typ){__VA_ARGS__};}while(0)
  #define DINIT_VALUE(ptr, ...) do{if(ptr == NULL){ptr = malloc(sizeof(DValue));}DNULLCROAK(ptr, "Can't init value" #__VA_ARGS__);*(typ*)ptr = (typ){__VA_ARGS__};}while(0)*/


#endif
