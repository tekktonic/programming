#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include "test_dtype.h"

int main(void)
{
    CU_pSuite list;
    CU_initialize_registry();
    list = CU_add_suite("List", NULL, NULL);
    CU_ADD_TEST(list, test_new_List);
    CU_ADD_TEST(list, test_List_enqueue);
    CU_ADD_TEST(list, test_List_dequeue);
    CU_ADD_TEST(list, test_List_push);
    CU_ADD_TEST(list, test_List_pop);
    CU_ADD_TEST(list, test_List_len);
    CU_ADD_TEST(list, test_List_delete);
    CU_ADD_TEST(list, test_List_free);
    CU_ADD_TEST(list, test_List_map);


    CU_ADD_TEST(list, test_new_Hash);
    CU_ADD_TEST(list, test_Hash_insert);
    CU_ADD_TEST(list, test_Hash_get);
	CU_ADD_TEST(list, test_Hash_del);
    CU_console_run_tests();
    return 0;
}
