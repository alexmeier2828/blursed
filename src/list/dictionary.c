#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

typedef struct {
	char* key;
	void* value;
} KeyValuePair; 

typedef struct {
	KeyValuePair* pairs;
	int size;
	int capacity;
} _Dict;

Dict* new_dict(){
	Dict* handle;
	_Dict* dict;

	handle = (Dict*)malloc(sizeof(Dict));
	if(handle == NULL){
		printf("ERROR: DICT: malloc error");
	}

	dict = malloc(sizeof(_Dict));
	if(dict == NULL){
		printf("ERROR: DICT: malloc error");
	}
	dict->size = 0;
	dict->capacity = 10;
	dict->pairs = malloc(sizeof(KeyValuePair) * 10);
	if(dict->pairs == NULL){
		printf("ERROR: DICT: malloc error");
	}
}

Dict* free_dict(Dict** p_handle, DictAction free_value){
	_Dict* dict;
	int i;

	dict = (_Dict*)(*p_handle)->obj;

	// free pairs
	for(i = 0; i < dict->size; i++){
		free_value(dict->pairs[i].value);
		free(dict->pairs[i].key);
	}
	free(dict->pairs);
	free(dict);
	free(*p_handle);
	*p_handle = NULL;
}

int dict_try_get(char* key, void** value){

}

int dict_add(char* key, void* value){

}
