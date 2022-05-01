#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"
#include "textpager.h"

#define IN_BOUNDS(x, upper_b)	\
	(x < upper_b && x >= 0)		

void free_row(void* p_row);
void free_char(void* p_char);
void scroll_to_fit(TextPager* p_pager);

TextPager* new_text_pager(int view_x, int view_y)
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
	p_pager->view_x = view_x;
	p_pager->view_y = view_y;

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

	scroll_to_fit(p_pager);
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
	} else if(d_col > 0) {
		// go to next line
		if(p_pager->crsr_r < p_pager->p_lines->size){
			p_pager->crsr_r++;
			p_pager->crsr_c = 0;
		}
	} else {
		// go to previous line
		if(p_pager->crsr_r > 0){
			p_pager->crsr_r --;
			p_row = ll_get(p_pager->p_lines, p_pager->crsr_r);
			p_pager->crsr_c = p_row->size -1;
		}
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

		// Scroll the pane if the cursor is now outside of the view pane
		scroll_to_fit(p_pager);
	}
}

void tp_delete(TextPager* p_pager){
	LList* p_row;
	LList* p_next_row;
	char* p_discard;
	char* p_temp;
	int i;
	
	// Get row
	p_row = (LList*)ll_get(p_pager->p_lines, p_pager->crsr_r);

	// if deleteing a newline, get rid of the next line if it exists
	if(*(char*)ll_get(p_row, p_pager->crsr_c) == '\n'){
		
		//copy next line to this one if it exists and delete
		if(p_pager->p_lines->size > p_pager->crsr_r + 1){
			p_next_row = (LList*)ll_get(p_pager->p_lines, p_pager->crsr_r + 1);

			while(p_next_row->size > 0){
				// copy characters over
				p_temp = (char*)ll_pop(p_next_row);
				ll_ins(p_row, p_pager->crsr_c, p_temp);
			}

			// delete next row
			ll_del(p_pager->p_lines, p_pager->crsr_r + 1);
			free_ll(&p_next_row, free_char);
		}
	}
	
	// delete character at cursor
	// free discarded character
	p_discard = ll_del(p_row, p_pager->crsr_c);
	free(p_discard);
}
	

char* tp_get_str(TextPager* p_pager){
	LList* p_row;
	int row_index;
	int col_index; 
	int draw_height;
	int final_size; 
	int i;
	char* cstring;
	char char_to_add;

	final_size = 0; 
	//first find out the size so we can make a giant c string.  
	for(row_index = p_pager->scroll_offset_y; row_index < p_pager->p_lines->size; row_index++){
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

	// This code alows the text pager to only show as many lines as can be displayed at a time
	// This will probably overestimate when there are wrapped lines, but thats ok because
	// curses will just take it anyway without displaying. 
	draw_height = p_pager->view_y + p_pager->scroll_offset_y;
	draw_height = draw_height < p_pager->p_lines->size ? draw_height : p_pager->p_lines->size;

	for(row_index = p_pager->scroll_offset_y; row_index < draw_height; row_index++){
		p_row = ll_get(p_pager->p_lines, row_index);
		for(col_index = 0; col_index < p_row->size; col_index++){
			char_to_add = *(char*)ll_get(p_row, col_index);

			//TODO this is really not an ideal way to handle tabs, but this will get refactore at some point when I implement a wrapper class to handle the cursor position and line wrapping
			switch(char_to_add){
				case '\t':
					cstring[i] = ' ';
					break;
				default:
					cstring[i] = char_to_add;
			}
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
	adjusted_cursor_y = p_pager->crsr_r - p_pager->scroll_offset_y;
	for(i = p_pager->scroll_offset_y; i <= p_pager->crsr_r; i++){
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

void scroll_to_fit(TextPager* p_pager){
	// if the cursor is now outside of the view pane, scroll to fit
	if(p_pager->crsr_r - p_pager->scroll_offset_y >= p_pager->view_y){
		p_pager->scroll_offset_y += p_pager->crsr_r - p_pager->scroll_offset_y - p_pager->view_y + 1;
	} 
	else if(p_pager->crsr_r < p_pager->scroll_offset_y){
		p_pager->scroll_offset_y = p_pager->crsr_r;
	}
}
