#ifndef DTYPE_TEST_H
#define DTYPE_TEST_H
#include "dtype.h"
#include <CUnit/CUnit.h>
extern int hash(const char *); // hash shouldn't normally be exported but it's useful for tests

void test_new_List(void)
{
    List a = new_List(1, 3);
    List l = new_List(5, (void*)5, (void*)321, (void*)382, "abcdef", a);
    // not much point in running the other tests if we can't even make a list
    CU_ASSERT_PTR_NOT_NULL_FATAL(l);
    CU_ASSERT_FATAL(l->car == (void*)5);

    CU_ASSERT_PTR_NOT_NULL_FATAL(l->cdr);
    CU_ASSERT_FATAL(l->cdr->car == (void*)321);

    CU_ASSERT_PTR_NOT_NULL_FATAL(l->cdr->cdr);
    CU_ASSERT_FATAL(l->cdr->cdr->car == (void*)382);

    CU_ASSERT_PTR_NOT_NULL_FATAL(l->cdr->cdr->cdr);
    CU_ASSERT_STRING_EQUAL_FATAL(l->cdr->cdr->cdr->car, "abcdef");

    CU_ASSERT_PTR_NOT_NULL_FATAL(l->cdr->cdr->cdr->cdr);
    CU_ASSERT_PTR_NOT_NULL_FATAL(l->cdr->cdr->cdr->cdr->car);
    CU_ASSERT_FATAL(l->cdr->cdr->cdr->cdr->car == a);
    CU_ASSERT_FATAL(((List)(l->cdr->cdr->cdr->cdr->car))->car == (void*)3);

    List_free(l, NULL);
    List_free(a, NULL);
}

void test_List_enqueue(void)
{
    List l = new_List(2, (void*)1, (void*)2);

    List_enqueue(l, (void*)3);
    List_enqueue(l, (void*)4);

    CU_ASSERT_PTR_NOT_NULL(l->cdr->cdr);
    CU_ASSERT(l->cdr->cdr->car == (void*)3);


    CU_ASSERT_PTR_NOT_NULL(l->cdr->cdr->cdr);
    
    CU_ASSERT(l->cdr->cdr->cdr->cdr == NULL);

    List_free(l, NULL);
}

void test_List_dequeue(void)
{
    List l = new_List(3, (void*)"man", (void*)"bar", (void*)"foo");
    char *str = (char*)List_dequeue(l);
    CU_ASSERT_STRING_EQUAL(str, "foo");
    CU_ASSERT(l->cdr->cdr == NULL);
    List_free(l, NULL);
}

void test_List_push(void)
{
    List l = new_List(2, (void*) 2, (void*) 3);
    List_push(&l, (void*)1);

    CU_ASSERT(l->car == (void*)1);

    List_free(l, NULL);
}

void test_List_pop(void)
{
    List l = new_List(2, (void*)2, (void*)1);
    int i = (int)List_pop(&l);
    CU_ASSERT(l->car == (void*)1);
    CU_ASSERT(i == 2);

    List_free(l, NULL);
}

void test_List_len(void)
{
    List l = new_List(3, (void*)4, (void*)1, (void*)1234);
    int len = List_len(l);
    printf("%d\n", len);
    CU_ASSERT_EQUAL(len, 3);
}

void test_List_delete(void)
{
    List l = new_List(3, (void*)3, (void*)8, (void*)0x432);

    List_delete(l, 0, NULL);
    CU_ASSERT(l->cdr->car == (void*)0x432);
    List_free(l, NULL);
}

void test_List_free(void)
{
    List l = new_List(2, malloc(sizeof(char)), malloc(sizeof(int)));
    // just making sure we don't segfault is really the only way to test here...
    List_free(l, free);
}

void *_internal_maptest(void *x)
{
    printf("x is %p\n", x);
    return (void*)(x + 1);
}

void test_List_map(void)
{
    List l = new_List(4, (void*)1, (void*)2, (void*)3, (void*)43);
    List test = List_map(l, _internal_maptest);

    printf("\n\n%p %p %p\n", test->car, test->cdr->car, test->cdr->cdr->car);
    CU_ASSERT((int)test->car == 2);
    CU_ASSERT((int)test->cdr->car == 3);
    CU_ASSERT((int)test->cdr->cdr->car == 4);
}

void test_new_Hash(void)
{
    Hash h = new_Hash(); // another segfault test
    free(h);
}


void test_Hash_insert(void) // other tests depend on this one, so fatal it is
{
    Hash h = new_Hash();
    const char *key1 = "foo";
    const char *key2 = "bar";
    const char *key3 = "meh"; // collides with "foo"

    Hash_insert(h, key1, (void*)5);
    Hash_insert(h, key2, (void*)"baz");
    CU_ASSERT_STRING_EQUAL_FATAL(h->keys[hash(key1)], key1);
    CU_ASSERT_FATAL(h->values[hash(key1)] == (void*)5);

    CU_ASSERT_STRING_EQUAL_FATAL(h->keys[hash(key2)], key2);
    CU_ASSERT_STRING_EQUAL_FATAL(h->values[hash(key2)], (void*)"baz");

    Hash_insert(h, key1, (void*)8);
    CU_ASSERT_FATAL(h->values[hash(key1)] == (void*)8);

    Hash_insert(h, key3, "hem");
    CU_ASSERT_STRING_EQUAL_FATAL(h->values[hash(key3)], "hem");
    Hash_insert(h, key3, "ehm");
}

void test_Hash_get(void)
{
    Hash h = new_Hash();
    Hash_insert(h, "foo", (void*)"meh");
    // may as well test some long keys
    Hash_insert(h, "aftwhacywkfcuaowfutwqftqwchouawfc", (void*)89);
    Hash_insert(h, "meh", (void*) "foo");

    CU_ASSERT_STRING_EQUAL(Hash_get(h, "foo"), (void*)"meh");
    CU_ASSERT(Hash_get(h, "aftwhacywkfcuaowfutwqftqwchouawfc") == (void*)89);
    CU_ASSERT_STRING_EQUAL(Hash_get(h, "meh"), (void*) "foo");
}

void test_Hash_del(void)
{
	Hash h = new_Hash();
	
	Hash_insert(h, "fyybar", (void*)"constant string");
	char *notconst = malloc(4);
	snprintf(notconst, 4, "abc");
	Hash_insert(h, "fim", (void*)notconst);

	Hash_del(h, "fim", free);

	CU_ASSERT(Hash_get(h, "fim") == NULL);
}

#endif



