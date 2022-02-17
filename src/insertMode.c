#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "linkedlist.h"
#include "textpager.h"
#include "buffer.h"
#include "editorState.h"
#include "editor"

void insert_mode(EditorState* p_state, int input_char){
	switch(input_char){
		case KEY_BACKSPACE:
			// TODO backspace key
			return;
		case KEY_ESCAPE:
			p_state->mode = NORMAL;
			return; 
	}

	bfr_put_char_to_curser(p_state->currentBuffer, (char)input_char);
	bfr_refresh(p_state->currentBuffer);
}
