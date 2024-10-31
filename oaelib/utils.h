#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFER(func) __attribute__((cleanup(func)))
#define POOL_SIZE 64 // items count in a buffer

struct iterator
{
	size_t size;
	void **buffer;
};

void *__unwrap_log__(void*, char*, int, char*);
#define unwrap(value)	\
	__unwrap_log__(value, (char*)__FILE__, __LINE__, (char*)__FUNCTION__)

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

/*
 * This hash library is inspired (copied) from this reference.
 * https://benhoyt.com/writings/hash-table-in-c/
 *
 * Legal Notice:
 * You may use however you want to, including the right godfather.
 *
 * It also uses `djb2` hashing function. 
 * reference: http://www.cse.yorku.ca/~oz/hash.html
*/

/*
 * hash struct consist of capacity, length and buffer.
 * it is a pretty simple and straight forward hash library.
*/
#define MAX_HASH_TABLE_CAPACITY 1024
typedef struct HASH_STRUCT hash_T;

/*
 * init hash table with default capacity,
 * it still needs improvement for allocating more than default capacity.
 *
 * TODO: More capacity.
*/
hash_T *init_hash(void);

/*
 * it will free the buffer first and then free the hash itself.
 * It may need to free all the keys, as in `benhoyt` implementation.
 *
 * But, for my use case i think it is fine to leave it as it is.
*/
void hash_free(hash_T*);

/*
 * It will return list of keys,
 * that are present int the hashmap.
*/
const char **hash_bucket(hash_T*);

/*
 * It will set the value if it founds the key in entry,
 * else it will create new entry.
*/
void hash_set(hash_T*, const char*, void*);

/*
 * it will loop through from hash_index till capacity.
 * if it found non-null value, it will return.
 * else null will be returned
*/
void *hash_get(hash_T*, const char*);

#endif // __UTILS_H__
