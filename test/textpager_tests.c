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
		cmocka_unit_test (new_tp_returns_non_null)
    };

    /* If setup and teardown functions are not
       needed, then NULL may be passed instead */

    int count_fail_tests =
        cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
