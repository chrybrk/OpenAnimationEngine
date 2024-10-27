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

void timeline_add_keyframe(timeline_T *timeline, keyframe_T *keyframe)
{
	list_push(timeline->keyframes, keyframe);
}

void timeline_draw(timeline_T *timeline)
{
	foreach(keyframe_T *item, list_iterator(timeline->keyframes), {
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
