#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <raylib.h>
#include <raymath.h>
#include <stddef.h>

typedef enum
{
	TEXT = 0
} object_kind_T;

typedef struct
{
	void (*draw)(void *object, float t, Vector2 position, Color color);
	object_kind_T kind;
} object_T;

typedef struct TEXT_OBJECT
{
	object_T base;
	char *text;
	float fontSize;
} text_T;

void draw(void *object, float t, Vector2 position, Color color);

object_T *init_text(const char *text, float fontSize);
void text_destroy(object_T **text);

#endif // __OBJECT_H__
