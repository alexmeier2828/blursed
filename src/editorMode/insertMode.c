#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "linkedlist.h"
#include "textpager.h"
#include "buffer.h"
#include "editorState.h"
#include "editorModes.h"

/**
 * handle insert mode keystrokes
 */
void insert_mode(EditorState* p_state, int input_char){
	switch(input_char){
		case KEY_ESCAPE:
			p_state->mode = NORMAL;
			break;
		case '\177':
			bfr_backspace(p_state->currentBuffer);
			bfr_refresh(p_state->currentBuffer);
			break;
		default:
			bfr_put_char_to_curser(p_state->currentBuffer, (char)input_char);
			bfr_refresh(p_state->currentBuffer);
			break;
	}
}

