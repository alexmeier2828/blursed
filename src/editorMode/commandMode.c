#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "linkedlist.h"
#include "textpager.h"
#include "buffer.h"
#include "editorState.h"
#include "editorModes.h"

void run_command(EditorState* p_state, char* command_str);
void write_command(EditorState* p_state, char* argument);

void command_mode(EditorState* p_state, int input_char){
	char* command_str;
	switch(input_char){
		case KEY_ESCAPE:
			p_state->mode = NORMAL;
			break;
		case '\n':
			command_str = tp_get_str(p_state->commandBuffer->p_pager);
			run_command(p_state, command_str);
			bfr_clear(p_state->commandBuffer);
			bfr_refresh(p_state->commandBuffer);
			p_state->mode = NORMAL;
			free(command_str);
			break;
		case '\177':
			bfr_backspace(p_state->commandBuffer);
			bfr_refresh(p_state->commandBuffer);
			break;
		default:
			bfr_put_char_to_curser(p_state->commandBuffer, (char)input_char);
			bfr_refresh(p_state->commandBuffer);
			break;
	}
}


void run_command(EditorState* p_state, char* command_str){
	char* command;
	char* argument;

	command = strtok(command_str, " ");
	if(command != NULL){
		if(strcmp(command, "e") == 0){
			argument = strtok(NULL, " ");
			if(argument != NULL){
				bfr_clear(p_state->currentBuffer);
				bfr_load_file(p_state->currentBuffer, argument);
				bfr_refresh(p_state->currentBuffer);
			}
		} else if(strcmp(command, "q") == 0) {
			endwin();
			exit(0);
		} else if(strcmp(command, "w") == 0) {
			argument = strtok(NULL, " ");
			write_command(p_state, argument);
		}
	}

}

/**
 * write currentBuffer to the file specified
 */
void write_command(EditorState* p_state, char* argument){
	if(argument != NULL){
		bfr_write_to_file(p_state->currentBuffer, argument);
	}else{
		if(p_state->currentBuffer->current_file_str != NULL){
			bfr_write_to_file(p_state->currentBuffer, p_state->currentBuffer->current_file_str);
		}else{
			//TODO do something when the user hasn't tried to buffer a file yet
		}
	}
}
