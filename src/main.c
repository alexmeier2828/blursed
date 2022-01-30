#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "buffer.h"

int main(int argc, char** argv){
	CharBuffer* pBuffer;
	char input_char; 

	pBuffer = create_buffer(50);

	// get input from keyboard in a loop
	while(1 == 1){
		initscr();
		addstr("test");
		refresh();

		input_char = getch();

		if(input_char != '\n')
		{
			buffer_put_char_to_curser(pBuffer, input_char);
			addstr(pBuffer->contents);
		}
	}

	return 0; 
}
