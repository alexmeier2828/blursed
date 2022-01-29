#ifndef BUFFER_H
#define BUFFER_H 0

/**
 * Header for struct to hold buffer stuff
 */
typedef struct BUFFER {
	char* contents;
	int capacity;
} CharBuffer;

/**
 * allocates space for a new charBuffer.  
 */
CharBuffer* create_buffer(int capacity);

/**
 * Frees alocated memory for charBuffer;
 * Sets handle to null
 */
void free_buffer(CharBuffer** pBufferHandle);

#endif
