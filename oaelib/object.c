#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

// draw functions for objects

void draw_text(void *object, float t, Vector2 position, Color color);
void draw_array(void *object, float t, Vector2 position, Color color);

typedef struct TEXT_OBJECT
{
	object_T base;
	char *text;
	float fontSize;
	animation_T *animation;
} text_T;

typedef struct ARRAY_STRUCT
{
	object_T base;
	int *elements;
	size_t size;
	Vector2 dsize;
	Vector2 gap;
	float fontSize;
	Color bg_color;
	animation_T *bg_animation;
	animation_T *fg_animation;
} array_T;

object_T *init_text(const char *text, float fontSize, animation_T *animation)
{
	text_T *tx = malloc(sizeof(struct TEXT_OBJECT));
	tx->base.draw = draw_text;
	tx->text = malloc((strlen(text) + 1) * sizeof(char));
	tx->text = strcpy(tx->text, text);
	tx->fontSize = fontSize;
	tx->animation = animation;

	return (object_T*)tx;
}

Vector2 text_get_size(object_T *text)
{
	text_T *tx = (text_T*)(text) - offsetof(text_T, base);

	return (Vector2) { MeasureText(tx->text, tx->fontSize), tx->fontSize };
}

void text_destroy(object_T **text)
{
	text_T *tx = (text_T*)(*text) - offsetof(text_T, base);

	if (tx)
	{
		free(tx->text);
		free(tx);
	}
}

void draw_text(void *object, float t, Vector2 position, Color color)
{
	text_T *text = (text_T*)object - offsetof(text_T, base);

	animation_properties_T animation_properties = {
		.color = color,
		.f1 = text->fontSize,
		.v2 = position
	};
	animation_flush(text->animation, t, &animation_properties);

	DrawText(text->text, animation_properties.v2.x, animation_properties.v2.y, animation_properties.f1, animation_properties.color);
}

object_T *init_array(size_t size, int elements[size], Vector2 dsize, Vector2 gap, float fontSize, Color bg_color, animation_T *bg_animation, animation_T *fg_animation)
{
	array_T *array = malloc(sizeof(struct ARRAY_STRUCT));
	array->base.draw = draw_array;
	array->size = size;
	array->elements = malloc(sizeof(int) * size);
	memcpy(array->elements, elements, sizeof(int) * size);
	array->dsize = dsize;
	array->gap = gap;
	array->fontSize = fontSize;
	array->bg_color = bg_color;
	array->bg_animation = bg_animation;
	array->fg_animation = fg_animation;
	return (object_T*)array;
}

Vector2 array_get_size(object_T *object)
{
	array_T *array = (array_T*)(object) - offsetof(array_T, base);
	return array->dsize;
}

void array_destroy(object_T **object)
{
	array_T *array = (array_T*)(*object) - offsetof(array_T, base);
	if (array)
		free(array);
}

void draw_array(void *object, float t, Vector2 position, Color color)
{
	array_T *array = (array_T*)object - offsetof(array_T, base);

	Vector2 element_size = (Vector2) { array->dsize.x / array->size, array->dsize.y };

	animation_properties_T bg_animation_props = {
		.color = array->bg_color,
		.v2 = position
	};
	animation_flush(array->bg_animation, t, &bg_animation_props);

	animation_properties_T fg_animation_props = {
		.color = color,
		.f1 = array->fontSize
	};
	animation_flush(array->bg_animation, t, &fg_animation_props);

	array->bg_color = bg_animation_props.color;
	position = bg_animation_props.v2;

	color = fg_animation_props.color;
	array->fontSize = fg_animation_props.f1;

	for (size_t i = 0; i < array->size; ++i)
	{
		Vector2 rel_position = (Vector2) { position.x + (element_size.x * i) + array->gap.x * i, position.y + array->gap.y };
		DrawRectangleV(rel_position, element_size, array->bg_color);

		char text[10]; snprintf(text, 10, "%d", array->elements[i]);
		int text_width = MeasureText(text, array->fontSize);

		DrawText(text, rel_position.x + element_size.x / 2 - (float)text_width / 2 - array->gap.x, rel_position.y + element_size.y / 2 - array->fontSize / 2, array->fontSize, color);
	}
}
