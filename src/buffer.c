#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "linkedlist.h"
#include "textpager.h"
#include "buffer.h"

// Macros
#define IS_CURSER_SAFE(b, d)	\
	(b->curser + d < b->capacity && 	\
	b->curser + d >= 0)

//Private functions
void set_current_file_str(CharBuffer* p_buffer, char* new_str);

// Header Implementation
CharBuffer* create_buffer(WINDOW* p_window){
	CharBuffer* p_buffer;
	int win_size_x, win_size_y;


	p_buffer = malloc(sizeof(CharBuffer));
	if(p_buffer == NULL){
		endwin();
		printf("BUFFER ERROR: MALLOC FAILED");
		exit(1);
	}

	//get window size
	getmaxyx(p_window, win_size_y, win_size_x);

	p_buffer->p_win = p_window; 
	p_buffer->p_pager = new_text_pager(win_size_x, win_size_y);
	p_buffer->current_file_str = NULL;
	
	return p_buffer;
}

void free_buffer(CharBuffer** pBufferHandle){
	//TODO find out how to free memory for windows 
	delwin((*pBufferHandle)->p_win);
	free_text_pager((&(*pBufferHandle)->p_pager));

	if((*pBufferHandle)->current_file_str != NULL){
		free((*pBufferHandle)->current_file_str);
	}

	free(*pBufferHandle);
	*pBufferHandle = NULL;
}

/**
 * puts character to buffer and advances curser
 */
void bfr_put_char_to_curser(CharBuffer* p_buffer, char c){
	switch(c){
		case '\t':
			tp_push(p_buffer->p_pager, ' ');
			tp_push(p_buffer->p_pager, ' ');
			break;
		default:
			tp_push(p_buffer->p_pager, c);
	}
}

/**
 * advances the curser d spaces 
 */
int bfr_move_curser(CharBuffer* p_buffer, int x, int y){
	int winx, winy;
	int win_size_x, win_size_y;

	//get window size
	getmaxyx(p_buffer->p_win, win_size_y, win_size_x);
	
	//get adjusted cursor
	tp_get_curses_cursor(p_buffer->p_pager, win_size_x, win_size_y, &winx, &winy);

	// move text pager curser 
	tp_move_row(p_buffer->p_pager, y);
	tp_move_col(p_buffer->p_pager, x);


}

void bfr_backspace(CharBuffer* p_buffer){
	//Call delete, then move the cursr to the left one space 
	if(p_buffer->p_pager->crsr_r != 0 || p_buffer->p_pager->crsr_c != 0){
		tp_move_col(p_buffer->p_pager, -1);
		tp_delete(p_buffer->p_pager);
	}
}

/**
 * Clears buffer, prints to window
 */
void bfr_clear(CharBuffer* p_buffer){
	int win_size_x, win_size_y;

	//get window size
	getmaxyx(p_buffer->p_win, win_size_y, win_size_x);

	free_text_pager(&(p_buffer->p_pager));
	p_buffer->p_pager = new_text_pager(win_size_x, win_size_y);
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
	if(file != NULL){
		//set the file string
		set_current_file_str(p_buffer, file_str);

		//read from file character by character
		// TODO need to check if this is any less efficient than using scanf or reading line by line
		while((read_char = fgetc(file)) != EOF){
			switch(read_char){
				case '\t':
					tp_push(p_buffer->p_pager, ' ');
					tp_push(p_buffer->p_pager, ' ');
					break;
				default:
					tp_push(p_buffer->p_pager, read_char);
			}
		}
		
		tp_move_col(p_buffer->p_pager, - p_buffer->p_pager->crsr_c);
		tp_move_row(p_buffer->p_pager, - p_buffer->p_pager->crsr_r);
		wmove(p_buffer->p_win, 0, 0);
		//close file stream
		fclose(file);
	} else {
		// TODO do something when file can't be opened
	}

}

void bfr_write_to_file(CharBuffer* p_buffer, char* file_str){
	FILE* file;
	char* pager_str;

	file = fopen(file_str, "w");	
	if(file != NULL)
	{
		set_current_file_str(p_buffer, file_str);
		pager_str = tp_get_str(p_buffer->p_pager);
		fprintf(file, "%s", pager_str);

		//cleanup
		fclose(file);
		free(pager_str);
	} else {
		// TODO do someting when the file can't be opened for writing
	}
}

void set_current_file_str(CharBuffer* p_buffer, char* new_str){
	if(p_buffer->current_file_str != NULL){
		free(p_buffer->current_file_str);
	}

	p_buffer->current_file_str = malloc(strlen(new_str) + 1);
	strcpy(p_buffer->current_file_str, new_str);
}
