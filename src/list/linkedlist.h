#ifndef LINKED_LIST
#define LINKED_LIST

typedef void (*Action) (void*) ;

typedef struct LINK {
	void* p_e;		/* pointer to element */
	struct LINK* p_next;	/* pointer to next link */
}Link;

typedef struct {
	Link* head;		/* head of the linked list */
	int size;
} LList;

/* 
 * alocate empty linked list
 */
LList* new_ll();

/*
 * dealocate whole list
 */
void free_ll(LList** pp_list, Action free_item);

/*
 * push to the end of list
 */
void ll_push(LList* p_list, void* item);

/* 
 * Insert item at index 
 * */
void ll_ins(LList* p_list, int i, void* item);

/*
 * returns item at index;
 */
void* ll_get(LList* p_list, int i);

/*
 * remove item at index
 */
void* ll_del(LList* p_list, int i);

/*
 * remove item at the end of list
 */
void* ll_pop(LList* p_list);
#endif
