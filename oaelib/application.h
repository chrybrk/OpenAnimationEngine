#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <raylib.h>

typedef struct APPLICATION_PROPERTIES_STRUCT
{
	int width;
	int height;
	int fps;
	char *title;
	void (*init)(void);
	void (*run)(void);
	void (*uninit)(void);
} application_properties_T;

extern application_properties_T *application_instance;

typedef struct CAPTURE_FRAME_STRUCT capture_frame_T;

capture_frame_T *init_capture_frame(const char *output_filepath, const char *converted_filepath, int total_duration);
bool capture_frame_should_end(capture_frame_T *capture_frame);
void capture_frame_push(capture_frame_T *capture_frame);
void capture_frame_unload(capture_frame_T *capture_frame);

#endif // __APPLICATION_H__
