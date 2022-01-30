#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

int main(int argc, char** argv){
	CharBuffer* pBuffer;
	char input_char; 

	pBuffer = create_buffer(50);

	// get input from keyboard in a loop
	while(1 == 1){
		input_char = getchar();

		if(input_char != '\n')
		{
			buffer_put_char_to_curser(pBuffer, input_char);
			printf("%s\n", pBuffer->contents);
		}
	}

	return 0; 
}
