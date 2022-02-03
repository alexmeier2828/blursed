#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "linkedlist.h"

int ACTION_CALLED = 0;

void new_ll_returns_non_null (void ** state)
{
	LList* list; 

 	list = new_ll();

    assert_true (list != NULL);
}

void free_test_func(void* item){
	assert_true(*((int*)item) == 69);
	ACTION_CALLED = 1;
} 

void free_ll_nulls_pointer (void ** state){
	int item; 
	LList* list;
	list = new_ll();
	free_ll(&list, free_test_func);
	assert_true(list == NULL);
}

void free_ll_nulls_calls_action (void ** state){
	int item; 
	LList* list;

	item = 69;
	list = new_ll();
	ll_push(list, &item);
	free_ll(&list, free_test_func);
	assert_true(list == NULL);
	assert_true(ACTION_CALLED);
}


void push_ll_items_in_correct_order (void ** state){
	int item1; 
	int item2;
	LList* list;

	item1 = 69;
	item2 = 420; 
	list = new_ll();

	ll_push(list, &item1);
	ll_push(list, &item2);

	assert_int_equal(item2, *((int*)ll_get(list, 0)));
	assert_int_equal(item1, *((int*)ll_get(list, 1)));
}
/* These functions will be used to initialize
   and clean resources up after each test run */
int setup (void ** state)
{
	ACTION_CALLED = 0;
    return 0;
}

int teardown (void ** state)
{
    return 0;
}


int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (new_ll_returns_non_null),
		cmocka_unit_test (free_ll_nulls_pointer), 
		cmocka_unit_test (free_ll_nulls_calls_action),
		cmocka_unit_test (push_ll_items_in_correct_order)
    };

    /* If setup and teardown functions are not
       needed, then NULL may be passed instead */

    int count_fail_tests =
        cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}



