#ifndef EDITOR_MODES
#define EDITOR_MODES

#define KEY_ESCAPE 27

void normal_mode(EditorState* p_state, int input_char);
void insert_mode(EditorState* p_state, int input_char);
void command_mode(EditorState* p_state, int input_char);

#endif
