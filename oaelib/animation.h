#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

typedef struct ANIMATION_STRUCT animation_T;

typedef struct ANIMATION_PROPERTIES_STRUCT
{
	int i1;
	float f1;
	Vector2 v2;
	Vector3 v3;
	Vector4 v4;
	Color color;
} animation_properties_T;

/* animation functions */
void fade_in_animation(float t, animation_properties_T init_properties, animation_properties_T *end_properties);
void fade_out_animation(float t, animation_properties_T init_properties, animation_properties_T *end_properties);
void color_interpolation_animation(float t, animation_properties_T init_properties, animation_properties_T *end_properties);
void move_animation(float t, animation_properties_T init_properties, animation_properties_T *end_properties);
void array_animation(float t, animation_properties_T init_properties, animation_properties_T *end_properties);

animation_T *init_animation();
void terminate_animation() __attribute__((destructor));
void animation_push(animation_T *animation, float start, float end, animation_properties_T animation_properties, void (*animation_function)(float, animation_properties_T, animation_properties_T*));
void animation_flush(animation_T *animation, float t, animation_properties_T *animation_properties);

#endif // __ANIMATION_H__
