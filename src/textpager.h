typedef struct {
	LList* p_lines;
	int crsr_r;
	int crsr_c;
} TextPager;

//TODO Add documentation for all of these
TextPager* new_text_pager();
void free_text_pager(TextPager** pp_pager);

/**
 * move row spaces up and down, and column spaces up or down
 */
void tp_move_row(TextPager* p_pager, int d_row){
void tp_move_col(TextPager* p_pager, int d_col){
void tp_push(TextPager* p_pager, char);

