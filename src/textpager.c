#include <stdlib.h>
#include <stdio.h>
#include "textpager.h"

#define IN_BOUNDS(x, upper_b)	\
	(x < upper_b && x >= 0)		

void free_row(void* p_row);
void free_char(void* p_char);

TextPager* new_text_pager()
{
	TextPager* p_pager;

	p_pager = malloc(sizeof(TextPager));
	p_pager-> p_lines = new_ll();
	p_pager-> crsr_r = 0; 
	p_pager-> crsr_c = 0;

	return p_pager;
}

void free_text_pager(TextPager* p_pager){
	int line, col;
	LList* p_lines; 

	p_lines = p_pager->p_lines;

	// Free lines first
	free_ll(&p_lines, free_row);
	free(*textpager);
	*textpager = NULL;
}


/**
 * move row spaces up and down
 */
void tp_move_row(TextPager* p_pager, int d_row){
	if(IN_BOUNDS(p_pager->crsr_r + d_row, p_pager->p_lines->size)){
		p_pager->crsr_r += d_row;			
	}
}

/**
 * move col n spaces up and down 
 */
void tp_move_col(TextPager* p_pager, int d_col){
	LList* p_row; 

	p_row = (LList*)p_pager->p_lines[p_pager->crsr_r];
	if(IN_BOUNDS(p_pager->crsr_c + d_col, p_row->size)){
		p_pager->crsr_c += d_col;			
	}
}

void tp_push(TextPager* p_pager, char c);

// private methods
void free_row(void* p_char_row){
	free_ll(&(LList*)p_char_row, free_char);
}

void free_char(void* p_char){
	free((char*)p_char);
}
