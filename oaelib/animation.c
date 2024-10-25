#include <raylib.h>
#include <raymath.h>
#include "animation.h"

typedef struct ANIMATION_STRUCT
{
	animation_kind_T kind;
	Vector2 position;
	Color color;
	float rotation;
} animation_T;

static void **animation_ptr_buffer = NULL;
static size_t animation_ptr_buffer_index = 0;
static size_t animation_ptr_buffer_current_size = 0;
static size_t animation_ptr_buffer_size = 64;

animation_T *init_animation(animation_kind_T kind, ...)
{
	animation_T *animation = malloc(sizeof(struct ANIMATION_STRUCT));
	if (animation == NULL)
	{
		perror("init_animation: failed to allocate memory: ");
		return NULL;
	}

	if (!animation_ptr_buffer || animation_ptr_buffer_index >= animation_ptr_buffer_current_size)
	{
		animation_ptr_buffer_current_size = animation_ptr_buffer_current_size + animation_ptr_buffer_size;

		if (animation_ptr_buffer)
			animation_ptr_buffer = realloc(animation_ptr_buffer, animation_ptr_buffer_current_size * 8);
		else
			animation_ptr_buffer = malloc(animation_ptr_buffer_current_size * 8);
	}

	animation_ptr_buffer[animation_ptr_buffer_index++] = animation;

	animation->kind = kind;
	
	va_list args;
	va_start(args, kind);

	switch (kind)
	{
		case FADE_IN:
		case FADE_OUT:
		{
			Color color = va_arg(args, Color);
			animation->color = color;
		}
	}

	return animation;
}

void animation_flush(animation_T *animation)
{

}

void terminate_animation()
{
	for (size_t i = 0; i < animation_ptr_buffer_index; ++i)
	{
		if (animation_ptr_buffer[i])
			free(animation_ptr_buffer[i]);
	}

	printf("Total freed: %ld bytes\n", sizeof(struct ANIMATION_STRUCT) * animation_ptr_buffer_index);
}
