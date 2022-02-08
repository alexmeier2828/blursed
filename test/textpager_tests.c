#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "linkedlist.h"
#include "textpager.h"

void new_tp_returns_non_null(void ** state){
	TextPager* p_pager;

	p_pager = new_text_pager();

	assert_non_null(p_pager);
}

void free_tp_nulls_ptr(void ** state){
	TextPager* p_pager;

	p_pager = new_text_pager();
	free_text_pager(&p_pager);

	assert_null(p_pager);
}

void tp_push_and_get_str(void ** state){
	TextPager* p_pager;
	char* string; 

	p_pager = new_text_pager();
	tp_push(p_pager, 'h');
	
	string = tp_get_str(p_pager);

	assert_string_equal("h", string);
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
		cmocka_unit_test (new_tp_returns_non_null),
		cmocka_unit_test (free_tp_nulls_ptr),
		cmocka_unit_test (tp_push_and_get_str)
    };

    /* If setup and teardown functions are not
       needed, then NULL may be passed instead */

    int count_fail_tests =
        cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
