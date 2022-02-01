#include <stdlib.h>
#include <ncurses.h>
#include "buffer.h"

// Macros
#define IS_CURSER_SAFE(b, d)	\
	(b->curser + d < b->capacity && 	\
	b->curser + d >= 0)

// Header Implementation
CharBuffer* create_buffer(WINDOW* p_window, char* file_str){
	CharBuffer* p_buffer;

	p_buffer = malloc(sizeof(CharBuffer));
	if(p_buffer == NULL){
		endwin();
		printf("BUFFER ERROR: MALLOC FAILED");
		exit(1);
	}

	p_buffer->p_win = p_window; 
	p_buffer->file_str = file_str;
	
	return p_buffer;
}

void free_buffer(CharBuffer** pBufferHandle){
	//TODO find out how to free memory for windows 
	delwin((*pBufferHandle)->p_win);
	free(*pBufferHandle);
	*pBufferHandle = NULL;
}

/**
 * puts character to buffer and advances curser
 */
void bfr_put_char_to_curser(CharBuffer* p_buffer, char c){
	waddch(p_buffer->p_win, c);
}

/**
 * advances the curser d spaces 
 */
int bfr_move_curser(CharBuffer* p_buffer, int x, int y){
	wmove(p_buffer->p_win, x, y);
}

/**
 * Clears buffer, prints to window
 */
void bfr_clear(CharBuffer* p_buffer){
	// TODO figure out how to clear curses window
}

/**
 * print buffer contents to curses window
 */
void bfr_refresh(CharBuffer* p_buffer){
	wrefresh(p_buffer->p_win); 
}

void bfr_save_to_file(CharBuffer* p_buffer){
	FILE* file;
	int i;
	
	// TODO sread from file. not implemented yet
	//file = fopen(p_buffer->file_str);
	
}
