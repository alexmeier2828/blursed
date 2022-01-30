#ifndef BUFFER_H
#define BUFFER_H 0

/**
 * Header for struct to hold buffer stuff
 */
typedef struct BUFFER {
	char* contents;
	int capacity;
	int curser; 
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

/**
 * puts character to buffer and advances curser
 */
void buffer_put_char_to_curser(CharBuffer* bufferHandle, char c);

/**
 * advances the curser d spaces 
 */
int buffer_move_curser(CharBuffer* bufferHandle, int d);

#endif
