#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "linkedlist.h"
#include "textpager.h"
#include "buffer.h"
#include "editorState.h"
#include "editorModes.h"

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


