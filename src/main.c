#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "linkedlist.h"
#include "textpager.h"
#include "buffer.h"

#define BUFFER_SIZE 500
#define KEY_ESCAPE 27

typedef enum {
	NORMAL,
	COMMAND,
	INSERT
} EditorModeEnum;

// TODO move this into its own file so it can live on the heap
// TODO buffer should be part of editor_state
// TODO should have a seperate buffer instance for command mode
typedef struct {
	EditorModeEnum mode;
	CharBuffer* p_buffer;
	int running; 
} EditorState;

// function definitions
void normal_mode(EditorState* p_state, int input_char);
void insert_mode(EditorState* p_state, int input_char);
void command_mode(EditorState* p_state, int input_char);

int main(int argc, char** argv){
	int input_char; 
	EditorState editor_state;
	WINDOW* p_main_window;
	bool should_open_file;

	// Command Line Arguments 
	if(argc > 2){
		printf("Usage: MicroEdit {file}");
		exit(1);
	}else if(argc == 2){
		//TODO configuration
		should_open_file = 1;
	}else {
		should_open_file = 0;
	}
	

	// Curses setup
	initscr();	/* Start curses mode */
	cbreak();	/* disables line buffering */
	noecho();   /* disables echoing keypresses */

	// TODO better way to set window size
	p_main_window = newwin(0, 0, 0, 0);
	
	// editor setup
	editor_state.p_buffer = create_buffer(p_main_window);
	if(should_open_file){
		bfr_load_file(editor_state.p_buffer, argv[1]);
	}
	bfr_refresh(editor_state.p_buffer);

	editor_state.mode = NORMAL;
	editor_state.running = TRUE;

	// get input from keyboard in a loop
	while(editor_state.running){
		input_char = getch();

		//mode switch
		switch(editor_state.mode){
			case NORMAL:
				normal_mode(&editor_state, input_char);
				break;
			case COMMAND:
				command_mode(&editor_state, input_char);
				break;
			case INSERT:
				insert_mode(&editor_state, input_char);
				break;
			default:
				printf("ERROR: encountered non implemented state");
				endwin();
				exit(1);
		}
	}

	endwin();
	return 0; 
}

void normal_mode(EditorState* p_state, int input_char){
	switch(input_char){
		case ':':
			p_state->mode = COMMAND;
			break;
		case 'i':
			p_state->mode = INSERT;
			break;
		//TODO for movment keys, it needs to also move the curses cursor
		case 'h':
			// left
			bfr_move_curser(p_state->p_buffer, -1, 0);
			break;
		case 'j':
			//move down
			bfr_move_curser(p_state->p_buffer, 0, 1);
			break;
		case 'k':
			//move up
			bfr_move_curser(p_state->p_buffer, 0, -1);
			break;
		case 'l':
			//move right
			bfr_move_curser(p_state->p_buffer, 1, 0);
			break;

	}
}

void insert_mode(EditorState* p_state, int input_char){
	switch(input_char){
		case KEY_BACKSPACE:
			return;
		case KEY_ESCAPE:
			p_state->mode = NORMAL;
			return; 
	}

	bfr_put_char_to_curser(p_state->p_buffer, (char)input_char);
}

void command_mode(EditorState* p_state, int input_char){
	switch(input_char){
		case 'q':
			p_state->running = FALSE;
			break;
		case KEY_ESCAPE:
			p_state->mode = NORMAL;
			break;
		// TODO commands for file manipulation
	}
}
