#include <stdlib.h>
#include "buffer.h"

// Macros
#define IS_CURSER_SAFE(b, d)	\
	(b->curser + d < b->capacity && 	\
	b->curser + d >= 0)

// Header Implementation
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
	if(IS_CURSER_SAFE(bufferHandle, 0))	
	{
		bufferHandle->contents[bufferHandle->curser] = c;
		buffer_move_curser(bufferHandle, 1);
	}
}

/**
 * advances the curser d spaces 
 */
int buffer_move_curser(CharBuffer* bufferHandle, int d){
	if(IS_CURSER_SAFE(bufferHandle, d))	
	{
		bufferHandle->curser += d;
		return 1; 
	}

	return 0; 
}
