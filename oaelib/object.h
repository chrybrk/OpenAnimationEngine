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

typedef struct TEXT_OBJECT
{
	object_T base;
	char *text;
	float fontSize;
	animation_T *animation;
} text_T;

object_T *init_text(const char *text, float fontSize, animation_T *animation);
void text_destroy(object_T **text);

#endif // __OBJECT_H__
