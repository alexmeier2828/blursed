#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "linkedlist.h"
#include "textpager.h"
#include "buffer.h"
#include "editorState.h"
#include "editorModes.h"

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
			bfr_move_curser(p_state->currentBuffer, -1, 0);
			break;
		case 'j':
			//move down
			bfr_move_curser(p_state->currentBuffer, 0, 1);
			break;
		case 'k':
			//move up
			bfr_move_curser(p_state->currentBuffer, 0, -1);
			break;
		case 'l':
			//move right
			bfr_move_curser(p_state->currentBuffer, 1, 0);
			break;
	}
}
