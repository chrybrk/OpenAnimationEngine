#ifndef __CORE_H__
#define __CORE_H__

#include <stdbool.h>
#include <raylib.h>
#include "object.h"
#include "utils.h"

typedef struct KEYFRAME_STRUCT keyframe_T;
typedef struct TIMELINE_STRUCT timeline_T;

/*
 * Function: init_keyframe(float start, float end, Vector2 position, Color color, object_T object))
 * -----------------------
 *  Creates keyframe.
 *
 *  start: Initial time (float)
 *  end: Duration (float)
 *  position: Position on the world (Vector2)
 *  color: Color of the object (Color)
 *  object: Virtual object (object_T)
 *
 * 	return: Keyframe (keyframe_T*) 
 * 
*/
keyframe_T *init_keyframe(float start, float end, Vector2 position, Color color, object_T *object);

/*
 * Function: init_timeline(float duration, bool reset)
 * -----------------------
 *  Creates timeline with duration, and reset variable.
 *
 * 	duration: Duration of the timeline (float)
 * 	reset: If true the animation will loop (bool)
 *
 * 	return: Timeline structure (timeline_T *)
 * 
*/
timeline_T *init_timeline(float duration, bool reset);

/*
 * Function: timeline_add_keyframe(timeline_T *timeline, keyframe_T keyframe)
 * -----------------------
 *  Adds keyframe to the timeline.
 *
 * 	timeline: Pointer to timeline (timeline_T *)
 * 	keyframe: New keyframe (keyframe_T)
 * 
*/
void timeline_add_keyframe(timeline_T *timeline, keyframe_T *keyframe);

/*
 * Function: timeline_draw(timeline_T *timeline)
 * -----------------------
 *  Draws element of keyframe.
 *
 * 	timeline: Pointer to timeline (timeline_T *)
 * 	keyframe: New keyframe (keyframe_T)
 * 
*/
void timeline_draw(timeline_T *timeline);

/*
 * Function: timeline_add_keyframe(timeline_T *timeline, keyframe_T keyframe)
 * -----------------------
 *  Adds keyframe to the timeline.
 *
 * 	timeline: Pointer to timeline (timeline_T *)
 * 	keyframe: New keyframe (keyframe_T)
 * 
*/
void timeline_update(timeline_T *timeline, float dt);

#endif // __CORE_H__
