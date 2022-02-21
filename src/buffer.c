#include <stdlib.h>
#include <ncurses.h>
#include "linkedlist.h"
#include "textpager.h"
#include "buffer.h"

// Macros
#define IS_CURSER_SAFE(b, d)	\
	(b->curser + d < b->capacity && 	\
	b->curser + d >= 0)

// Header Implementation
CharBuffer* create_buffer(WINDOW* p_window){
	CharBuffer* p_buffer;

	p_buffer = malloc(sizeof(CharBuffer));
	if(p_buffer == NULL){
		endwin();
		printf("BUFFER ERROR: MALLOC FAILED");
		exit(1);
	}

	p_buffer->p_win = p_window; 
	p_buffer->p_pager = new_text_pager();
	
	return p_buffer;
}

void free_buffer(CharBuffer** pBufferHandle){
	//TODO find out how to free memory for windows 
	delwin((*pBufferHandle)->p_win);
	free_text_pager((&(*pBufferHandle)->p_pager));
	free(*pBufferHandle);
	*pBufferHandle = NULL;
}

/**
 * puts character to buffer and advances curser
 */
void bfr_put_char_to_curser(CharBuffer* p_buffer, char c){
	int winx, winy;
	int win_size_x, win_size_y;
	char* string;

	//get window size
	getmaxyx(p_buffer->p_win, win_size_y, win_size_x);

	tp_push(p_buffer->p_pager, c);
	wmove(p_buffer->p_win, 0, 0);

	string =  tp_get_str(p_buffer->p_pager);

	// TODO I don't think its nessecary to add string in here.  it can be the callers responsibility to refresh the window
	waddstr(p_buffer->p_win, string);
	
	//get adjusted cursor
	tp_get_curses_cursor(p_buffer->p_pager, win_size_x, win_size_y, &winx, &winy);
	wmove(p_buffer->p_win, winy, winx);

	free(string);
}

/**
 * advances the curser d spaces 
 */
int bfr_move_curser(CharBuffer* p_buffer, int x, int y){
	int winx, winy;
	int win_size_x, win_size_y;

	//get window size
	getmaxyx(p_buffer->p_win, win_size_y, win_size_x);
	
	// move text pager curser 
	tp_move_row(p_buffer->p_pager, y);
	tp_move_col(p_buffer->p_pager, x);

	//get adjusted cursor
	tp_get_curses_cursor(p_buffer->p_pager, win_size_x, win_size_y, &winx, &winy);
	wmove(p_buffer->p_win, winy, winx);
}

void bfr_backspace(CharBuffer* p_buffer){
	int winx, winy;
	int win_size_x, win_size_y;

	//Call delete, then move the cursr to the left one space 
	if(p_buffer->p_pager->crsr_r != 0 || p_buffer->p_pager->crsr_c != 0){
		tp_move_col(p_buffer->p_pager, -1);
		tp_delete(p_buffer->p_pager);

		//get window size
		getmaxyx(p_buffer->p_win, win_size_y, win_size_x);
		
		//get adjusted cursor
		tp_get_curses_cursor(p_buffer->p_pager, win_size_x, win_size_y, &winx, &winy);
		wmove(p_buffer->p_win, winy, winx);
	}
}

/**
 * Clears buffer, prints to window
 */
void bfr_clear(CharBuffer* p_buffer){
	free_text_pager(&(p_buffer->p_pager));
	p_buffer->p_pager = new_text_pager();
}

/**
 * print buffer contents to curses window
 */
void bfr_refresh(CharBuffer* p_buffer){
	char* string;
	int winx, winy;
	int win_size_x, win_size_y;

	//get window size
	getmaxyx(p_buffer->p_win, win_size_y, win_size_x);
	
	string = tp_get_str(p_buffer->p_pager);
	werase(p_buffer->p_win);
	wmove(p_buffer->p_win, 0, 0);
	waddstr(p_buffer->p_win, string);

	//get adjusted cursor
	tp_get_curses_cursor(p_buffer->p_pager, win_size_x, win_size_y, &winx, &winy);
	wmove(p_buffer->p_win, winy, winx);
	
	// Refresh window
	wrefresh(p_buffer->p_win); 

	free(string);
}

void bfr_load_file(CharBuffer* p_buffer, char* file_str){
	FILE* file;
	char read_char;
	int i;
	
	//open file for reading
	file = fopen(file_str, "r");
	if(file == NULL){
		printf("ERROR: BUFFER: Failed to open file: %s", file_str);
		endwin();
		exit(1);
	}

	//read from file character by character
	// TODO need to check if this is any less efficient than using scanf or reading line by line
	while((read_char = fgetc(file)) != EOF){
		tp_push(p_buffer->p_pager, read_char);
	}
	
	tp_move_col(p_buffer->p_pager, - p_buffer->p_pager->crsr_c);
	tp_move_row(p_buffer->p_pager, - p_buffer->p_pager->crsr_r);
	wmove(p_buffer->p_win, 0, 0);
	//close file stream
	fclose(file);
}

void bfr_save_to_file(CharBuffer* p_buffer){
	printf("NotImplemented bfr_save_to_file");
	exit(1);
}
