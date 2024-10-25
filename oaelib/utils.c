#include "utils.h"

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
