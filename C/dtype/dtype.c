#include "dtype.h"
#define FREE_WRAP(x, free_func) {if (free_func) free_func(x);}

List new_List(int count, ...)
{
    List ret = malloc(sizeof(struct List_s));
    List cur = ret;
    va_list args;
    assert(cur != NULL);

    if (count)
    {
	va_start(args, count);


	while(count--)
	{
	    cur->car = va_arg(args, void*);
	    if (count)
	    {
		cur->cdr = malloc(sizeof(struct List_s));
		assert(cur->cdr != NULL);
		cur = cur->cdr;
	    }
	}
	va_end(args);
    }
    else
	cur->car = NULL;
    cur->cdr = NULL;
    return ret;
}

void List_enqueue(List list1, void *item)
{
    List cur = list1;

    do
    {
	if (cur->car == NULL)
	{
	    cur->car = item;
	    return;
	}

	if (cur->cdr != NULL)
	{
	    cur = cur->cdr;
	}

    } while(cur->cdr != NULL);

    cur->cdr = new_List(1, item);
}

void *List_dequeue(List list)
{
    List cur = list;
    List last = cur;

    void *ret;
    for(; cur->cdr != NULL; cur = cur->cdr)
	last = cur;
    ret = cur->car;
    last->cdr = NULL;

    free(cur);
    return ret;
}

void List_push(List *list, void *item)
{
    List new = new_List(1, item);
    new->cdr = *list;
    *list = new;
}

void *List_pop(List *list)
{
    void *ret = (*list)->car;
    List oldcar = *list;
    *list = (*list)->cdr;
    free(oldcar);
    return ret;
}

int List_len(List list)
{
    int i = 0;
    for(;list->cdr != NULL;)
    {
	list = list->cdr;
	++i;
    }
    return i + 1;
}

void List_delete(List list, int index, void (*free_func)(void *))
{
    List cur = list;
    List last = cur;

    int i = 0;
    for (; i < index && cur->cdr != NULL; cur = cur->cdr, ++i)
		last = cur;

    if (i == index)
    {
		FREE_WRAP(cur->car, free_func);
		last->cdr = cur->cdr;
		if (cur == list) {
			*cur = *cur->cdr;
			List cdr = cur->cdr;
			List_delete(cdr, 0, free_func); // cdr is bypassed now that it's copied
		} else {

			free(cur);
			cur = NULL;
		}
    }
}

void List_free(List list, void (*free_func)(void *))
{
    if (list == NULL)
	return;
    else if (list->cdr)
	List_free(list->cdr, free_func);
    else
    {
		FREE_WRAP(list->car, free_func);

		free(list);
    }
}

List List_map(List list, void *(*f)(void*))
{
    List ret = new_List(0);
    for(;list->cdr != NULL; list = list->cdr)
    {
		void *item = f(list->car);
		List_enqueue(ret, item);
    }
    return ret;
}

bool List_contains(List list, void *data)
{
    for(;list->cdr != NULL; list = list->cdr)
    {
		if (list->car == data)
			return true;
    }

    return false;
}

Hash new_Hash(void)
{
    Hash ret = malloc(sizeof(struct Bucket));
    assert(ret);
    ret->next = NULL;
    memset(ret->keys, '\0', BUCKET_SIZE * sizeof(char*)); // make sure we get some decent null checks
    memset(ret->values, '\0', BUCKET_SIZE * sizeof(void*));
    return ret;
}

int hash(const char *string)
{
    int len = strlen(string) + 1; // strlen doesn't include null
    int sum = 0;
    for (int i = 0; i < len; ++i)
    {
		sum += (int)string[i];
    }

    return sum % BUCKET_SIZE;
}

void Hash_insert(Hash h, const char *key, void *value)
{
    size_t offset = hash(key);

    if (!h->keys[offset] || strcmp(h->keys[offset], key) == 0) // If either we already have an entry for the key or there are no keys there
    {
		h->keys[offset] = key;
		h->values[offset] = value;
    }
    else
    {
	if (!h->next)
	{
	    h->next = new_Hash();
	}
	Hash_insert(h->next, key, value);
    }
}   

void *Hash_get(Hash h, const char *key)
{
    int offset = hash(key);

    if (h->keys[offset] != NULL)
    {
	if (strcmp(h->keys[offset], key) == 0)
	{
	    return h->values[offset];
	}
	else if (h->next)
	{
	    return Hash_get(h->next, key);
	}
    }

    return NULL;
}

void Hash_del(Hash h, const char *key, void (*free_func)(void*))
{
    size_t offset = hash(key);
    if (h->keys[offset] && strcmp(h->keys[offset], key) == 0)
    {
		FREE_WRAP(h->values[offset], free_func);
		h->values[offset] = NULL;
		h->keys[offset] = NULL;
    }
    else if (h->next)
    {
		Hash_del(h->next, key, free_func);
    }
}

void Hash_kill(Hash h, void (*free_func)(void*))
{
    if (h->next)
	Hash_kill(h->next, free_func);

    for (size_t i = 0; i < BUCKET_SIZE; i++)
    {
	if (h->keys[i])
	    Hash_del(h, h->keys[i], free_func);
    }
    free(h);
}

FHash new_FHash(void)
{
    FHash ret = malloc(sizeof(struct FBucket));
    assert(ret);
    ret->next = NULL;
    memset(ret->keys, '\0', BUCKET_SIZE * sizeof(char*)); // make sure we get some decent null checks
    memset(ret->values, '\0', BUCKET_SIZE * sizeof(void*));
    return ret;
}

void FHash_insert(FHash h, const char *key, Func1 value)
{
    size_t offset = hash(key);

    if (!h->keys[offset] || strcmp(h->keys[offset], key) == 0) // If either we already have an entry for the key or there are no keys there
    {
	h->keys[offset] = key;
	h->values[offset] = value;
    }
    else
    {
	if (!h->next)
	{
	    h->next = new_FHash();
	}
	FHash_insert(h->next, key, value);
    }
}   



void (**FHash_get(FHash h, const char *key))(void*)
{
    size_t offset = hash(key);

    if (h->keys[offset] != NULL)
    {
	if (strcmp(h->keys[offset], key) == 0)
	{
	    return h->values[offset];
	}
	else if (h->next)
	{
	    return FHash_get(h->next, key);
	}
    }

    return NULL;
}

void FHash_del(FHash h, const char *key)
{
    size_t offset = hash(key);

    if (strcmp(h->keys[offset], key) == 0)
    {
	h->values[offset] = NULL;
	h->keys[offset] = NULL;
    }
    else if (h->next)
    {
	FHash_del(h->next, key);
    }
}

void FHash_kill(FHash h)
{
    if (h->next)
	FHash_kill(h);
    free(h);
}
