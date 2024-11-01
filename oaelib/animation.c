#include <raylib.h>
#include <raymath.h>
#include "animation.h"
#include "utils.h"

float time_relation(float t, float s, float e)
{
	return (t - s) / (e - s);
}

void fade_in_animation(float t, animation_properties_T init_properties, animation_properties_T *end_properties)
{
	end_properties->color = Fade(end_properties->color, t);
}

void fade_out_animation(float t, animation_properties_T init_properties, animation_properties_T *end_properties)
{
	end_properties->color = Fade(end_properties->color, 1.0f - t);
}

void color_interpolation_animation(float t, animation_properties_T init_properties, animation_properties_T *end_properties)
{
	unsigned char r = Lerp(init_properties.color.r, end_properties->color.r, t);
	unsigned char g = Lerp(init_properties.color.g, end_properties->color.g, t);
	unsigned char b = Lerp(init_properties.color.b, end_properties->color.b, t);
	unsigned char a = Lerp(init_properties.color.a, end_properties->color.a, t);

	end_properties->color = (Color) { r, g, b, a };
}

void move_animation(float t, animation_properties_T init_properties, animation_properties_T *end_properties)
{
	end_properties->v2 = Vector2MoveTowards(end_properties->v2, init_properties.v2, Vector2Distance(end_properties->v2, init_properties.v2) * t);
}

void array_animation(float t, animation_properties_T init_properties, animation_properties_T *end_properties)
{
	end_properties->i1 = init_properties.i1;
}

typedef struct ANIMATION_STRUCT
{
	list_T *animations;
} animation_T;

struct animation_push_node
{
	float start;
	float end;
	animation_properties_T animation_properties;
	void (*animation_function)(float, animation_properties_T, animation_properties_T*);
};

static void **animation_ptr_buffer = NULL;
static size_t animation_ptr_buffer_index = 0;
static size_t animation_ptr_buffer_current_size = 0;
static size_t animation_ptr_buffer_size = 64;

animation_T *init_animation()
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

		if (animation_ptr_buffer) animation_ptr_buffer = realloc(animation_ptr_buffer, animation_ptr_buffer_current_size * 8);
		else animation_ptr_buffer = malloc(animation_ptr_buffer_current_size * 8);

		if (animation_ptr_buffer == NULL)
		{
			perror("init_animation: failed to allocate memory: ");
			return NULL;
		}
	}

	animation->animations = init_list(sizeof(struct animation_push_node));

	return animation;
}

void animation_push(animation_T *animation, float start, float end, animation_properties_T animation_properties, void (*animation_function)(float, animation_properties_T, animation_properties_T*))
{
	struct animation_push_node *node = malloc(sizeof(struct animation_push_node));
	node->start = start;
	node->end = end;
	node->animation_properties = animation_properties;
	node->animation_function = animation_function;
	list_push(animation->animations, node);
}

void animation_flush(animation_T *animation, float t, animation_properties_T *animation_properties)
{
	foreach(struct animation_push_node *item, list_iterator(animation->animations), {
		if (item->start <= t)
			item->animation_function(time_relation(t, item->start, item->end), item->animation_properties, animation_properties);
	});
}

void terminate_animation()
{
	for (size_t i = 0; i < animation_ptr_buffer_index; ++i)
	{
		if (animation_ptr_buffer[i])
		{
			animation_T *animation = ((animation_T*)animation_ptr_buffer[i]);
			list_free(animation->animations);

			free(animation_ptr_buffer[i]);
		}
	}
}
