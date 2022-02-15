#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"
#include "textpager.h"

#define IN_BOUNDS(x, upper_b)	\
	(x < upper_b && x >= 0)		

void free_row(void* p_row);
void free_char(void* p_char);

TextPager* new_text_pager()
{
	TextPager* p_pager;

	p_pager = malloc(sizeof(TextPager));

	if(p_pager == NULL){
		printf("ERROR: TP: malloc error");
		exit(1);
	}
	
	p_pager-> p_lines = new_ll();
	p_pager-> crsr_r = 0; 
	p_pager-> crsr_c = 0;

	//first row
	ll_push(p_pager->p_lines, new_ll());

	return p_pager;
}

void free_text_pager(TextPager** pp_pager){
	int line, col;
	LList* p_lines; 

	p_lines = (*pp_pager)->p_lines;

	// Free lines first
	free_ll(&p_lines, free_row);
	free(*pp_pager);
	*pp_pager = NULL;
}


/**
 * move row spaces up and down
 */
void tp_move_row(TextPager* p_pager, int d_row){
	LList* new_row;

	// no need to do anything if we are already on the right row
	if(d_row == 0){
		return;
	}

	if(IN_BOUNDS(p_pager->crsr_r + d_row, p_pager->p_lines->size)){
		p_pager->crsr_r += d_row;			
		new_row = ll_get(p_pager->p_lines, p_pager->crsr_r);

		//shift the curser left if the line is shorter then the previous one
		if(p_pager->crsr_c > new_row->size){
			p_pager->crsr_c = new_row->size - 1;
		}
	}
}

/**
 * move col n spaces up and down 
 */
void tp_move_col(TextPager* p_pager, int d_col){
	LList* p_row; 
	
	// no need to do anything if we are already on the right col
	if(d_col == 0){
		return;
	}

	p_row = (LList*)ll_get(p_pager->p_lines, p_pager->crsr_r);
	if(IN_BOUNDS(p_pager->crsr_c + d_col, p_row->size)){
		p_pager->crsr_c += d_col;			
	}
}

void tp_push(TextPager* p_pager, char c){
	LList* p_row; 
	char* p_char_handle;
	int i, size_diff; 
	LList* new_row;

	
	//make rows up to cursor if its out of bounds
	size_diff = p_pager->crsr_r + 1 - p_pager->p_lines->size;
	for(i = 0; i < size_diff; i++){
		ll_push(p_pager->p_lines, new_ll());
	}
	

	// allocate space for character
	p_char_handle = malloc(sizeof(char));
	if(p_char_handle == NULL){
		printf("ERROR: TP: malloc error");
		exit(1);
	}

	*p_char_handle = c;

	// get row, and push character to the location of cursor
	p_row = (LList*)ll_get(p_pager->p_lines, p_pager->crsr_r);
	ll_ins(p_row, p_pager->crsr_c, p_char_handle);
	p_pager->crsr_c++;
	
	// create new line on new line
	if(c == '\n'){
		//add carage return
		p_char_handle = malloc(sizeof(char));
		if(p_char_handle == NULL){
			printf("ERROR: TP: malloc error");
			exit(1);
		}
		//*p_char_handle = '\r';
		//ll_ins(p_row, p_pager->crsr_c, p_char_handle);
		
		//copy end of line to new row
		new_row = new_ll();
		size_diff = p_row->size - p_pager->crsr_c;
		for(i = 0; i < size_diff; i++){
			p_char_handle = (char*)ll_pop(p_row);
			ll_ins(new_row, 0, p_char_handle);
		}

		ll_ins(p_pager->p_lines, p_pager->crsr_r + 1, new_row);
		p_pager->crsr_c = 0;  // reset cursor
		p_pager->crsr_r++;
	}
}

char* tp_get_str(TextPager* p_pager){
	LList* p_row;
	int row_index;
	int col_index; 
	int final_size; 
	int i;
	char* cstring;

	final_size = 0; 
	//first find out the size so we can make a giant c string.  
	for(row_index = 0; row_index < p_pager->p_lines->size; row_index++){
		p_row = ll_get(p_pager->p_lines, row_index);
		final_size += p_row->size;
	}

	//allocate memory for cstring
	cstring = malloc(sizeof(char) * final_size + 1);
	if(cstring == NULL){
		printf("ERROR: TP: malloc error");
		exit(1);
	}

	// itterate through pager
	i = 0;
	for(row_index = 0; row_index < p_pager->p_lines->size; row_index++){
		p_row = ll_get(p_pager->p_lines, row_index);
		for(col_index = 0; col_index < p_row->size; col_index++){
			cstring[i] = *(char*)ll_get(p_row, col_index);
			i++;
		}
	}

	cstring[final_size] = '\0';
	return cstring;
}

void tp_get_curses_cursor(TextPager* p_pager, int win_size_x, int win_size_y, int* x, int* y){
	int adjusted_cursor_x, adjusted_cursor_y;
	int	i; 
	LList* row;
	

	// this is the curser value if none of the lines wrap
	adjusted_cursor_y = p_pager->crsr_r;
	for(i = 0; i <= p_pager->crsr_r; i++){
		row = (LList*)ll_get(p_pager->p_lines, i);
		if(row->size > win_size_x){
			adjusted_cursor_y += row->size / win_size_x;
		}
	}

	adjusted_cursor_x = p_pager->crsr_c % win_size_x;
	
	*x = adjusted_cursor_x;
	*y = adjusted_cursor_y;
}

// private methods
void free_row(void* p_char_row){
	free_ll((LList**)&p_char_row, free_char);
}

void free_char(void* p_char){
	free((char*)p_char);
}

