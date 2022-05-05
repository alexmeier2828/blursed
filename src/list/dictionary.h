#ifndef DICT
#define DICT

typedef void (*DictAction) (void*) ;

typedef struct {
	void* obj;
} Dict;

Dict* new_dict(DictAction);
Dict* free_dict(Dict** dict);
int dict_try_get(Dict* handle, char* key, void** value);
void dict_add(Dict* handle, char* key, void* value);

#endif
