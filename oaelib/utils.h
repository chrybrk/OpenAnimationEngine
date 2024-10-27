#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>

#define DEFER(func) __attribute__((cleanup(func)))

#define POOL_SIZE 64 // items count in a buffer

struct iterator
{
	size_t size;
	void **buffer;
};

// #define foreach(cast_to, iterator, body) { for (size_t __index = 0; __index < iterator.size; ++__index) { cast_to item = (cast_to)(iterator.buffer[__index]); body } }
#define foreach(VAR, ITER, BODY) \
	{ \
		for (size_t _item_index = 0; _item_index < ITER.size; ++_item_index) \
		{ \
			VAR = ITER.buffer[_item_index]; \
			BODY \
		} \
	} \

/*
 * Allocate a buffer of POOL_SIZE * item_size (initially)
 * Then, if index hits size - 1 realloc the buffer;
*/
typedef struct LIST_STRUCT list_T;

/*
 * Function: init_list(size_t item_size)
 * -----------------------
 *  Creates a dynamic list.
 *
 *  item_size: Size of the item that needs to be pushed. (size_t)
 *
 *  return: List structure; (list_T)
 * 
*/
list_T *init_list(size_t item_size);

/*
 * Function: list_push(list_T *list, void *item)
 * -----------------------
 *  Push item into list.
 *
 *  list: Pointer to list (list_T *)
 *  item: Item that needs to be inserted (void *)
 * 
*/
void list_push(list_T *list, void *item);

/*
 * Function: list_pop(list_T *list)
 * -----------------------
 *  Removes the last item from the list.
 *
 *  list: Pointer to list (list_T *)
 * 
*/
void list_pop(list_T *list);

/*
 * Function: list_get(list_T *list, size_t index)
 * -----------------------
 *  Gets item from the list.
 *
 *  list: Pointer to list (list_T *)
 *  index: Index of the item in the list (size_t)
 *
 *  return: Item (void *)
 * 
*/
void *list_get(list_T *list, size_t index);

/*
 * Function: list_iterator(list_T *list)
 * -----------------------
 *  Gives iterator to iterate.
 *
 *  list: Pointer to list (list_T *)
 *
 *  return: Iterator
 * 
*/
struct iterator list_iterator(list_T *list);

/*
 * Function: list_size(list_T *list)
 * -----------------------
 *  Returns the size of the list aka current index.
 *
 *  list: Pointer to list (list_T *)
 *
 *  return: Size of list (size_t)
 * 
*/
size_t list_size(list_T *list);

/*
 * Function: list_free(list_T *list)
 * -----------------------
 *  Free the list and its element.
 *
 *  list: Pointer to list (list_T *)
 * 
*/
void list_free(list_T *list);

#endif // __UTILS_H__
