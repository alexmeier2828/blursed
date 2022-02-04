typedef struct {
	LList* lines;
	int cursor_x;
	int cursor_y;
} TextPager;

TextPager* new_text_pager();
void free_text_pager();
void tp_ins(TextPager p_pager, int index);
void tp_push(TextPager p_pager, char);
