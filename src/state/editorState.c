#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "linkedlist.h"
#include "textpager.h"
#include "buffer.h"
#include "editorState.h"

/**
 * Constructor
 */
EditorState* new_editor_state(){
	EditorState* p_editor_state;

	p_editor_state = malloc(sizeof(EditorState));
	if(p_editor_state == NULL){
		printf("ERROR: EditorState:Constructor Malloc Error");
	}

	return p_editor_state;
}

/** 
 * Destructor
 */
void free_editor_state(EditorState** p_editor_state){
	free(*p_editor_state);
	*p_editor_state = NULL;
}
