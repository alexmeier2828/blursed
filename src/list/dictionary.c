#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

typedef struct {
	char* key;
	void* value;
} KeyValuePair; 

typedef struct {
	KeyValuePair* pairs;
	int size;
	int capacity;
	DictAction free_value;
} _Dict;

// Private defs
void add_pair_and_resize(_Dict* dict, char* key, void* value);

// Implementation
Dict* new_dict(DictAction free_value){
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
	dict->free_value = free_value;
}

Dict* free_dict(Dict** p_handle){
	_Dict* dict;
	int i;

	dict = (_Dict*)(*p_handle)->obj;

	// free pairs
	for(i = 0; i < dict->size; i++){
		dict->free_value(dict->pairs[i].value);
		free(dict->pairs[i].key);
	}
	free(dict->pairs);
	free(dict);
	free(*p_handle);
	*p_handle = NULL;
}

int dict_try_get(Dict* handle, char* key, void** value){
	int i;
	_Dict* dict;
	
	dict = (_Dict*)handle->obj;

	for(i = 0; i < dict->size; i++){
		if(strcmp(key, dict->pairs[i].key) == 0){
			*value = dict->pairs[i].value;
			return 1;
		}
	}

	return 0;
}

void dict_add(Dict* handle, char* key, void* value){
	int i;
	_Dict* dict;
	
	dict = (_Dict*)handle->obj;

	for(i = 0; i < dict->size; i++){
		if(strcmp(key, dict->pairs[i].key) == 0){
			dict->free_value(dict->pairs[i].value);
			dict->pairs[i].value = value;
			return;
		}
	}

	// add the new pair
	add_pair_and_resize(dict, key, value);
}

// Private functions
void add_pair_and_resize(_Dict* dict, char* key, void* value){
	KeyValuePair* temp;

	if(dict->capacity <= dict->size){
		temp = malloc(sizeof(KeyValuePair) * dict->capacity * 2);
		if(temp == NULL){
			printf("ERROR: DICT: malloc error");
			exit(1);
		}

		memcpy(temp, dict->pairs, sizeof(KeyValuePair) * dict->capacity);
		free(dict->pairs);
		dict->pairs = temp;
	}

	dict->pairs[dict->size].value = value;
	strcpy(dict->pairs[dict->size].key, key);
}
