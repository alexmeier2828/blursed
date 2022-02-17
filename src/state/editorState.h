#ifndef EDITOR_STATE
#define EDITOR_STATE

typedef enum {
	NORMAL,
	COMMAND,
	INSERT
} EditorModeEnum;

// TODO should have a seperate buffer instance for command mode
typedef struct {
	EditorModeEnum mode;
	CharBuffer* currentBuffer;
	int running; 
} EditorState;

/**
 * Constructor
 */
EditorState* new_editor_state();

/** 
 * Destructor
 */
void free_editor_state(EditorState** p_editor_state);

#endif
