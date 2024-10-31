#include "core.h"

typedef struct KEYFRAME_STRUCT
{
	float start;
	float end;
	Vector2 position;
	Color color;
	object_T *object;
} keyframe_T;

typedef struct TIMELINE_STRUCT
{
	float duration;
	float currentTime;
	bool reset;
	list_T *keyframes;
} timeline_T;

Vector2 get_alignment_on_surface(alignment_T alignment, Vector2 surface_size, Vector2 object_size, Vector2 offset)
{
	Vector2 result;

	switch (alignment)
	{
		case top: result = (Vector2){ surface_size.x / 2.0f - object_size.x / 2.0f + offset.x, offset.y }; break;
		case bottom: result = (Vector2){ surface_size.x / 2.0f - object_size.x / 2.0f + offset.x, surface_size.y + offset.y }; break;
		case left: result = (Vector2){ offset.x, surface_size.y / 2.0f - object_size.y / 2.0f + offset.y }; break;
		case right: result = (Vector2){ surface_size.x + offset.x, surface_size.y / 2.0f - object_size.y / 2.0f + offset.y }; break;
		case tleft: result = (Vector2){ offset.x, offset.y }; break;
		case tright: result = (Vector2){ offset.x + surface_size.x, offset.y }; break;
		case bleft: result = (Vector2){ offset.x, surface_size.y + offset.y }; break;
		case bright: result = (Vector2){ offset.x + surface_size.x, surface_size.y + offset.y }; break;
		case center: result = (Vector2){ surface_size.x / 2.0f - object_size.x / 2.0f + offset.x, surface_size.y / 2.0f - object_size.y / 2.0f + offset.y }; break;
	}

	return result;
}

Vector2 offset_alignment(Vector2 position, Vector2 size, float offset_x, float offset_y)
{
	return (Vector2) { position.x - size.x / 2.0f + offset_x, position.y - size.y / 2.0f + offset_y };
}

keyframe_T *init_keyframe(float start, float end, Vector2 position, Color color, object_T *object)
{
	keyframe_T *keyframe = malloc(sizeof(struct KEYFRAME_STRUCT));
	if (keyframe == NULL)
	{
		perror("init_keyframe: Failed to allocate memory: ");
		return NULL;
	}

	keyframe->start = start;
	keyframe->end = end;
	keyframe->position = position;
	keyframe->color = color;
	keyframe->object = object;

	return keyframe;
}

timeline_T *init_timeline(float duration, bool reset)
{
	timeline_T *timeline = malloc(sizeof(struct TIMELINE_STRUCT));
	if (timeline == NULL)
	{
		perror("init_timeline: Failed to allocate memory: ");
		return NULL;
	}

	timeline->duration = duration;
	timeline->currentTime = 0.0f;
	timeline->reset = reset;
	timeline->keyframes = init_list(sizeof(struct KEYFRAME_STRUCT));

	return timeline;
}

void timeline_set_duration(timeline_T *timeline, float duration)
{
	timeline->duration = duration;
}

float timeline_get_duration(timeline_T *timeline)
{
	return timeline->duration;
}

float timeline_get_max_duration_from_keyframe(timeline_T *timeline)
{
	float max = 0.0f;

	foreach(keyframe_T *item, list_iterator(timeline->keyframes), {
			max = item->end > max ? item->end : max;
	});

	return max;
}

float timeline_get_current_time(timeline_T *timeline)
{
	return timeline->currentTime;
}

void timeline_add_keyframe(timeline_T *timeline, keyframe_T *keyframe)
{
	list_push(timeline->keyframes, keyframe);
}

void timeline_draw(timeline_T *timeline)
{
	foreach(keyframe_T *item, list_iterator(timeline->keyframes), {
		if (item->start <= timeline->currentTime && item->end >= timeline->currentTime)
			item->object->draw(item->object, (timeline->currentTime - item->start) / (item->end - item->start), item->position, item->color);
	});
}

// TODO: Add keyboard controls.
// TODO: Add play / pause state.
void timeline_update(timeline_T *timeline, float dt)
{
	if (timeline->currentTime >= timeline->duration)
	{
		if (timeline->reset) timeline->currentTime = 0.0f;
	}
	else timeline->currentTime += dt;
}
