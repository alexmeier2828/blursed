#ifndef BUFFER_H
#define BUFFER_H 0

/**
 * Header for struct to hold buffer stuff
 */
typedef struct BUFFER {
	TextPager* p_pager;	
	WINDOW* p_win;		
	char* file_str;
} CharBuffer;

/**
 * allocates space for a new charBuffer.  
 */
CharBuffer* create_buffer(WINDOW* p_window, char* file_str);

/**
 * Frees alocated memory for charBuffer;
 * Sets handle to null
 */
void free_buffer(CharBuffer** pBufferHandle);

/**
 * puts character to buffer and advances curser
 */
void bfr_put_char_to_curser(CharBuffer* p_buffer, char c);

/**
 * advances the curser d spaces 
 */
int bfr_move_curser(CharBuffer* p_buffer, int x, int y);

/**
 * Clears buffer, prints to window
 */
void bfr_clear(CharBuffer* p_buffer);

/**
 * print buffer contents to curses window
 */
void bfr_refresh(CharBuffer* p_buffer);

/**
 * save buffer to file
 */
void bfr_save_to_file(CharBuffer* p_buffer);

#endif
