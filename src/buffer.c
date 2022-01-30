#include <stdlib.h>
#include "buffer.h"


CharBuffer* create_buffer(int capacity){
	CharBuffer* bufferHandle;

	bufferHandle = malloc(sizeof(CharBuffer));
	bufferHandle->capacity = capacity;
	bufferHandle->contents = malloc(sizeof(char) * (capacity + 1));
	bufferHandle->curser = 0; 

	//add null terminator
	bufferHandle->contents[bufferHandle->capacity] = '\0';

	return bufferHandle;
}

void free_buffer(CharBuffer** pBufferHandle){
	free((*pBufferHandle)->contents);
	free(*pBufferHandle);

	*pBufferHandle = NULL;
}

/**
 * puts character to buffer and advances curser
 */
void buffer_put_char_to_curser(CharBuffer* bufferHandle, char c){
	if(bufferHandle->curser < bufferHandle->capacity &&
	   bufferHandle->curser >= 0)	
	{
		bufferHandle->contents[bufferHandle->curser] = c;
		buffer_move_curser(bufferHandle, 1);
	}
}

/**
 * advances the curser d spaces 
 */
int buffer_move_curser(CharBuffer* bufferHandle, int d){
	if(bufferHandle->curser + d < bufferHandle->capacity &&
	   bufferHandle->curser + d >= 0)	
	{
		bufferHandle->curser += d;
		return 1; 
	}

	return 0; 
}
