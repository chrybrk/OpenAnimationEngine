#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "object.h"

void draw(void *object, float t, Vector2 position, Color color)
{
	switch (((object_T*)object)->kind)
	{
		case TEXT:
		{
			text_T *obj = (text_T*)object - offsetof(text_T, base);

			DrawText(obj->text, position.x, position.y, obj->fontSize, color);

			break;
		}
	}
}

object_T *init_text(const char *text, float fontSize)
{
	text_T *tx = malloc(sizeof(struct TEXT_OBJECT));
	tx->base.draw = draw;
	tx->base.kind = TEXT;
	tx->text = malloc((strlen(text) + 1) * sizeof(char));
	tx->text = strcpy(tx->text, text);
	tx->fontSize = fontSize;

	return (object_T*)tx;
}

void text_destroy(object_T **text)
{
	text_T *tx = (text_T*)(*text) - offsetof(text_T, base);

	if (tx)
		free(tx->text);
}
