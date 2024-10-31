#include "utils.h"

void *__unwrap_log__(void *value, char *file, int line, char *function)
{
	if (value == NULL)
	{
		fprintf(stdout, "%s:%d :: In %s: \n\tExpected not NULL value, but got NULL.\n", file, line, function);
		exit(EXIT_FAILURE);
	}
	
	return value;
}

typedef struct LIST_STRUCT {
	void **buffer;
	size_t size;
	size_t index;
	size_t item_size;
} list_T;

list_T *init_list(size_t item_size)
{
	list_T *list = malloc(sizeof(struct LIST_STRUCT));
	if (list == NULL)
	{
		perror("init_list::Failed to allocate list: ");
		return NULL;
	}

	list->buffer = malloc(item_size * POOL_SIZE);
	if (list->buffer == NULL)
	{
		perror("init_list::Failed to allocate buffer: ");
		return NULL;
	}

	list->index = 0;
	list->item_size = item_size;
	list->size = POOL_SIZE;

	return list;
}

void list_push(list_T *list, void *item)
{
	if (list->buffer == NULL)
	{
		list->buffer = malloc(list->item_size * POOL_SIZE);
		list->index = 0;
		list->size = POOL_SIZE;
	}

	if (list->index >= list->size)
	{
		list->buffer = realloc(list->buffer, (list->size + POOL_SIZE) * list->item_size);
		list->size = list->size + POOL_SIZE;
	}

	if (list->buffer == NULL)
	{
		perror("list_push::Failed to allocate buffer: ");
		return;
	}

	list->buffer[list->index++] = item;
}

void list_pop(list_T *list)
{
	if (list->index > 0) list->index--;
}

size_t list_size(list_T *list)
{
	return list->index;
}

void *list_get(list_T *list, size_t index)
{
	if (index < list->index)
		return list->buffer[index];

	return NULL;
}

struct iterator list_iterator(list_T *list)
{
	return (struct iterator) {
		.size = list->index,
		.buffer = list->buffer
	};
}

void list_free(list_T *list)
{
	free(list->buffer);
	free(list);
}

typedef struct {
	const char *key;
	void *value;
} hash_entry;

typedef struct HASH_STRUCT {
	hash_entry *buffer;
	ssize_t capacity;
	ssize_t length;
	char **keys;
} hash_T;

/*
 * Hashing function
 * 
 * It is a djb2 hashing function.
 * reference: http://www.cse.yorku.ca/~oz/hash.html
 *
 * Legal Notice:
 * I am not the godfather of this hashing function but if it works on your project, use it.
*/
unsigned long long
hash_function(const char *string)
{
	// magic number is supposed to be `33`.
	unsigned long hash = 5381;
	int c;

	while ((c = *string++) != 0)
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

hash_T *init_hash(void)
{
	hash_T *hash = malloc(sizeof(struct HASH_STRUCT));
	unwrap(hash);

	hash->length = 0;
	hash->capacity = MAX_HASH_TABLE_CAPACITY;
	hash->buffer = malloc(sizeof(hash_entry) * hash->capacity);
	memset(hash->buffer, 0, sizeof(hash_entry) * hash->capacity);
	unwrap(hash->buffer);

	hash->keys = NULL;

	return hash;
}

void hash_free(hash_T *hash)
{
	free(hash->keys);
	free(hash->buffer);
	free(hash);
}

void hash_set(hash_T *hash, const char *key, void *value)
{
	unsigned long long magic_number = hash_function(key);
	ssize_t index = (ssize_t)(magic_number & (MAX_HASH_TABLE_CAPACITY - 1));

	int if_found = 0;

	while (hash->buffer[index].key != NULL)
	{
		if (strcmp(key, hash->buffer[index].key) == 0)
		{
			hash->buffer[index].value = value;
			if_found = 1;
			break;
		}

		index++;
		if (index >= MAX_HASH_TABLE_CAPACITY) index = 0;
	}

	if (if_found == 0)
	{
		hash->buffer[index].key = (const char*)strdup(key);
		hash->buffer[index].value = value;
		hash->length++;

		if (hash->keys)
			hash->keys = realloc(hash->keys, sizeof(char*) * hash->length);
		else
			hash->keys = malloc(sizeof(char*));

		hash->keys[hash->length - 1] = malloc(strlen(key) + 1);
		hash->keys[hash->length - 1] = (char*)strdup(key);
	}
}

void* hash_get(hash_T *hash, const char *key)
{
	unsigned long long magic_number = hash_function(key);
	ssize_t index = (ssize_t)(magic_number & (MAX_HASH_TABLE_CAPACITY - 1));

	while (hash->buffer[index].key != NULL)
	{
		if (strcmp(key, hash->buffer[index].key) == 0)
			return hash->buffer[index].value;

		index++;
		if (index >= MAX_HASH_TABLE_CAPACITY) index = 0;
	}
	
	return NULL;
}

const char **hash_bucket(hash_T *hash)
{
	return (const char**)hash->keys;
}
