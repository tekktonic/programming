#ifndef DTYPE_H
#define DTYPE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <stdbool.h>

#define BUCKET_SIZE 30

struct List_s
{
    void *car;
    struct List_s *cdr;
};


struct Bucket
{
    const char *keys[BUCKET_SIZE];
    void *values[BUCKET_SIZE];
    struct Bucket *next;
};
typedef struct List_s *List;
typedef struct Bucket *Hash;
typedef struct FBucket *FHash;

typedef List Queue;
typedef List Stack;

#define LIST_FOREACH(list, content) {for(List list_elm = list; list_elm; list_elm = list_elm->cdr) { content }}

typedef void(**Func1)(void*);
struct FBucket
{
    const char *keys[BUCKET_SIZE];
    Func1 values[BUCKET_SIZE];
    struct FBucket *next;
};

struct Vect_s
{
    int x, y;
};

typedef struct Vect_s Vect;

List new_List(int count, ...);

void List_enqueue(List list, void *item);
void *List_dequeue(List list);
void List_push(List *list, void *item);
void *List_pop(List *list);
int List_len(List list);
void List_delete(List list, int index, void (*free_func)(void *));
void List_free(List list, void (*free_func)(void *));
List List_map(List list, void *(*f)(void*));
bool List_contains(List list, void *data);

Hash new_Hash(void);
void Hash_insert(Hash hash, const char *key, void *value);
void *Hash_get(Hash hash, const char *key);
void Hash_del(Hash h, const char *key, void (*free_func)(void*));
void Hash_kill(Hash h, void (*free_func)(void*));

FHash new_FHash(void);
void FHash_insert(FHash hash, const char *key, Func1 value);
void (**FHash_get(FHash hash, const char *key))(void*);
void FHash_kill(FHash h);

Vect vect(int x, int y);
#endif
