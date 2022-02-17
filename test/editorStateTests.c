#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <ncurses.h>
#include "linkedlist.h"
#include "textpager.h"
#include "buffer.h"
#include "editorState.h"

/* These functions will be used to initialize
   and clean resources up after each test run */

void new_editor_state_returns_instance(void **state){
	EditorState* editorState;

	editorState = new_editor_state();

	assert_non_null(editorState);
}

void free_editor_state_nulls_pointer(void **state){
	EditorState* editorState;

	editorState = new_editor_state();
	free_editor_state(&editorState);
	
	assert_null(editorState);
}

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
		cmocka_unit_test (new_editor_state_returns_instance),
		cmocka_unit_test (free_editor_state_nulls_pointer)
    };

    /* If setup and teardown functions are not
       needed, then NULL may be passed instead */

    int count_fail_tests =
        cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
