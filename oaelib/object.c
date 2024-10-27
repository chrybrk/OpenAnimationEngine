#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "object.h"

// draw functions for objects

/* TEXT DRAW FUNCTION */
void draw_text(void *object, float t, Vector2 position, Color color);

object_T *init_text(const char *text, float fontSize, animation_T *animation)
{
	text_T *tx = malloc(sizeof(struct TEXT_OBJECT));
	tx->base.draw = draw_text;
	tx->base.kind = TEXT;
	tx->text = malloc((strlen(text) + 1) * sizeof(char));
	tx->text = strcpy(tx->text, text);
	tx->fontSize = fontSize;
	tx->animation = animation;

	return (object_T*)tx;
}

void text_destroy(object_T **text)
{
	text_T *tx = (text_T*)(*text) - offsetof(text_T, base);

	if (tx)
		free(tx->text);
}

void draw_text(void *object, float t, Vector2 position, Color color)
{
	text_T *text = (text_T*)object - offsetof(text_T, base);
	animation_properties_T animation_properties = { .color = color };
	animation_flush(text->animation, t, &animation_properties);

	DrawText(text->text, position.x, position.y, text->fontSize, animation_properties.color);
}
