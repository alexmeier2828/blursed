#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "linkedlist.h"
#include "textpager.h"
#include "buffer.h"
#include "editorState.h"
#include "editorModes.h"

#define BUFFER_SIZE 500

int main(int argc, char** argv){
	int input_char; 
	EditorState* p_editor_state;
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
	p_editor_state = new_editor_state();
	p_editor_state->currentBuffer = create_buffer(p_main_window);
	if(should_open_file){
		bfr_load_file(p_editor_state->currentBuffer, argv[1]);
	}
	bfr_refresh(p_editor_state->currentBuffer);

	p_editor_state->mode = NORMAL;
	p_editor_state->running = TRUE;

	// get input from keyboard in a loop
	while(p_editor_state->running){
		input_char = wgetch(p_main_window);
		bfr_refresh(p_editor_state->currentBuffer);

		//mode switch
		switch(p_editor_state->mode){
			case NORMAL:
				normal_mode(p_editor_state, input_char);
				break;
			case COMMAND:
				command_mode(p_editor_state, input_char);
				break;
			case INSERT:
				insert_mode(p_editor_state, input_char);
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
