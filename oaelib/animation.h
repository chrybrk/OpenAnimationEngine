#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct ANIMATION_STRUCT animation_T;

typedef enum 
{
	FADE_IN = 0,
	FADE_OUT
} animation_kind_T;

animation_T *init_animation(animation_kind_T kind, ...);
void terminate_animation() __attribute__((destructor));
void animation_flush(animation_T *animation);

#endif // __ANIMATION_H__
