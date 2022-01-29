#include <stdlib.h>
#include "buffer.h"

CharBuffer* create_buffer(int capacity){
	CharBuffer* bufferHandle;

	bufferHandle = malloc(sizeof(CharBuffer));
	bufferHandle->capacity = capacity;
	bufferHandle->contents = malloc(sizeof(char) * (capacity + 1));

	//add null terminator
	bufferHandle->contents[bufferHandle->capacity] = '\0';

	return bufferHandle;
}

void free_buffer(CharBuffer** pBufferHandle){
	free((*pBufferHandle)->contents);
	free(*pBufferHandle);

	*pBufferHandle = NULL;
}

