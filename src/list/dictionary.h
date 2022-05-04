#ifndef DICT
#define DICT

typedef void (*DictAction) (void*) ;

typedef struct {
	void* obj;
} Dict;

Dict* new_dict();
Dict* free_dict(Dict** dict, DictAction free_value);
int dict_try_get(char* key, void** value);
int dict_add(char* key, void* value);

#endif
