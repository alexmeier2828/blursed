#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

void simple_free_item(void* item){
	free(item);
}
void dict_new_dict_returns_not_null(void ** state){
	Dict* dict;
	dict = new_dict(simple_free_item);
	
	assert_true(dict != NULL);
	free_dict(&dict);
	assert_true(dict == NULL);
}

/* These functions will be used to initialize
   and clean resources up after each test run */
int setup (void ** state)
{
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
        cmocka_unit_test (dict_new_dict_returns_not_null),
    };

    /* If setup and teardown functions are not
       needed, then NULL may be passed instead */

    int count_fail_tests =
        cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}



