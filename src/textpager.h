#ifndef TEXT_PAGER
#define TEXT_PAGER
typedef struct {
	LList* p_lines;
	int crsr_r;
	int crsr_c;
} TextPager;

/*
 * allocate new text pager instance
 */
TextPager* new_text_pager();

/*
 * Deallocate pager instance
 */
void free_text_pager(TextPager** pp_pager);

/*
 * move row spaces up and down
 */
void tp_move_row(TextPager* p_pager, int d_row);

/*
 * move row spaces left and right
 */
void tp_move_col(TextPager* p_pager, int d_col);

/*
 * push character to pager
 */
void tp_push(TextPager* p_pager, char);

/*
 * Gets the contents of the buffer in string form
 * TODO this will work but it's super ineficient 
 */
char* tp_get_str(TextPager* p_pager);

/*
 * convert cursor cordinates to a curses window that might display this text pager.
 * the resulting x/y conversion is placed in the parameters x and y. 
 */
void tp_get_curses_cursor(TextPager* p_pager, int win_size_x, int win_size_y, int* x, int* y);

#endif
