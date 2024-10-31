#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <raylib.h>
#include <raymath.h>
#include <stddef.h>
#include "animation.h"

typedef struct
{
	void (*draw)(void *object, float t, Vector2 position, Color color);
} object_T;

typedef struct TEXT_OBJECT text_T;
typedef struct ARRAY_STRUCT array_T;

object_T *init_text(const char *text, float fontSize, animation_T *animation);
Vector2 text_get_size(object_T *text);
void text_destroy(object_T **text);

object_T *init_array(size_t size, int elements[size], Vector2 dsize, Vector2 gap, float fontSize, Color bg_color, animation_T *bg_animation, animation_T *fg_animation);
Vector2 array_get_size(object_T *object);
void array_destroy(object_T **object);

#endif // __OBJECT_H__
