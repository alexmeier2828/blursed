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

void tp_push_newline_new_row_is_made(void ** state){
	TextPager* p_pager;
	char* string;

	p_pager = new_text_pager();
	tp_push(p_pager, 'h');
	tp_push(p_pager, 'e');
	tp_push(p_pager, 'l');
	tp_push(p_pager, 'l');
	tp_push(p_pager, 'o');
	tp_push(p_pager, '\n');
	tp_push(p_pager, 'w');
	tp_push(p_pager, 'o');
	tp_push(p_pager, 'r');
	tp_push(p_pager, 'l');
	tp_push(p_pager, 'd');
	
	string = tp_get_str(p_pager);

	assert_int_equal(2, p_pager->p_lines->size);
	assert_string_equal("hello\nworld", string);
	
}

void tp_push_multiple_newlines_end_of_string_carries(void **state){
	TextPager* pager; 
	char* string;

	pager = new_text_pager();

	tp_push(pager, 'h');
	tp_push(pager, 'e');
	tp_push(pager, 'l');
	tp_push(pager, 'l');
	tp_push(pager, 'o');
	tp_push(pager, ' ');
	tp_push(pager, 'w');
	tp_push(pager, 'o');
	tp_push(pager, 'r');
	tp_push(pager, 'l');
	tp_push(pager, 'd');
	
	// now move cursor left to w
	tp_move_col(pager, -5);

	//push 3 newlines
	tp_push(pager, '\n');
	tp_push(pager, '\n');
	tp_push(pager, '\n');

	string = tp_get_str(pager);

	assert_int_equal(4, pager->p_lines->size);
	assert_string_equal("hello \n\n\nworld", string);
}

void tp_mov_col__move_left_on_first_line__cursor_moves_left(void **state){
	TextPager* pager;
	int winx, winy;
	char* string;

	pager = new_text_pager();

	tp_push(pager, 'a');
	tp_push(pager, 'b');
	tp_push(pager, 'c');
	tp_push(pager, 'd');
	tp_push(pager, 'e');
	
	//check cursor position
	assert_int_equal(5, pager->crsr_c);
	
	//move cursor left 1
	tp_move_col(pager, -1);


	tp_push(pager, 'f');
	string = tp_get_str(pager);

	//get reported window cordinates
	tp_get_curses_cursor(pager, 50, 50, &winx, &winy);

	//check cursor again
	assert_int_equal(5, pager->crsr_c);
	assert_int_equal(5, winx);
	assert_int_equal(0, winy);
	assert_string_equal("abcdfe", string);
}

void tp_delete_removes_character(void **state){
	TextPager* tp;
	char* string;

	tp = new_text_pager();

	tp_push(tp, 'h');
	tp_push(tp, 'e');
	tp_push(tp, 'l');
	tp_push(tp, 'l');
	tp_push(tp, 'o');

	tp_move_col(tp, -1);
	tp_delete(tp);

	string = tp_get_str(tp);
	assert_string_equal("hell", string);
}

void tp_delete_begining_of_line(void **state){
	TextPager* tp;
	char* string;

	tp = new_text_pager();

	tp_push(tp, 'h');
	tp_push(tp, 'e');
	tp_push(tp, 'l');
	tp_push(tp, 'l');
	tp_push(tp, 'o');
	tp_push(tp, '\n');

	tp_move_col(tp, -1);
	tp_delete(tp);

	string = tp_get_str(tp);
	assert_string_equal("hello", string);
}

void tp_delete_begining_of_line_one_char(void **state){
	TextPager* tp;
	char* string;

	tp = new_text_pager();

	tp_push(tp, 'h');
	tp_push(tp, 'e');
	tp_push(tp, 'l');
	tp_push(tp, 'l');
	tp_push(tp, 'o');
	tp_push(tp, '\n');
	tp_push(tp, 'h');

	tp_move_col(tp, -1);
	tp_delete(tp);
	tp_move_col(tp, -1);
	tp_delete(tp);

	string = tp_get_str(tp);
	assert_string_equal("hello", string);
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
		cmocka_unit_test (tp_push_and_get_str),
		cmocka_unit_test (tp_push_newline_new_row_is_made),
		cmocka_unit_test (tp_push_multiple_newlines_end_of_string_carries),
		cmocka_unit_test (tp_mov_col__move_left_on_first_line__cursor_moves_left),
		cmocka_unit_test (tp_delete_removes_character),
		cmocka_unit_test (tp_delete_begining_of_line),
		cmocka_unit_test (tp_delete_begining_of_line_one_char)
    };

    /* If setup and teardown functions are not
       needed, then NULL may be passed instead */

    int count_fail_tests =
        cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
