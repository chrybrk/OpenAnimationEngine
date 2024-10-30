#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include "application.h"

#define writef(...) ({  writef_function(__VA_ARGS__, NULL); })
char *writef_function(char *s, ...)
{
	// allocate small size buffer
	size_t buffer_size = 64; // bytes
	char *buffer = (char*)malloc(buffer_size);

	if (buffer == NULL)
	{
		perror("failed to allocate memory: ");
		return NULL;
	}

	va_list ap;
	va_start(ap, s);

	int nSize = vsnprintf(buffer, buffer_size, s, ap);
	if (nSize < 0)
	{
		free(buffer);
		va_end(ap);
	}

	// if buffer does not have enough space then extend it.
	if (nSize >= buffer_size)
	{
		buffer_size = nSize + 1;
		buffer = (char*)realloc(buffer, buffer_size);

		if (buffer == NULL)
		{
			perror("failed to allocate memory: ");
			return NULL;
		}

		va_end(ap);

		va_start(ap, s);
		vsnprintf(buffer, buffer_size, s, ap);
	}

	va_end(ap);

	return buffer;
}

typedef struct CAPTURE_FRAME_STRUCT
{
	int width;
	int height;
	int fps;
	int frames;
	int total_frames;
	int frame_data_size;
	char *output_filepath;
	char *converted_filepath;
	FILE *output_file;
} capture_frame_T;

capture_frame_T *init_capture_frame(const char *output_filepath, const char *converted_filepath, int total_duration)
{
	capture_frame_T *capture_frame = malloc(sizeof(struct CAPTURE_FRAME_STRUCT));
	if (!capture_frame)
	{
		perror("failed to allocate memory for capture_frame: ");
		return NULL;
	}
	capture_frame->width = application_instance->width;
	capture_frame->height = application_instance->height;
	capture_frame->fps = application_instance->fps;
	capture_frame->frames = 0;
	capture_frame->total_frames = total_duration * capture_frame->fps;
	capture_frame->frame_data_size = capture_frame->width * capture_frame->height * 4;
	capture_frame->output_filepath = malloc(strlen(output_filepath));
	capture_frame->output_filepath = strcpy(capture_frame->output_filepath, output_filepath);
	capture_frame->converted_filepath = malloc(strlen(converted_filepath));
	capture_frame->converted_filepath = strcpy(capture_frame->converted_filepath, converted_filepath);
	capture_frame->output_file = fopen(output_filepath, "wb");
	if (!capture_frame->output_file)
	{
		perror("failed to open file: ");
		free(capture_frame);
		return NULL;
	}
	return capture_frame;
}

void capture_frame_push(capture_frame_T *capture_frame)
{
	Image image = LoadImageFromScreen();
	fwrite(image.data, 1, capture_frame->frame_data_size, capture_frame->output_file);
	UnloadImage(image);
	capture_frame->frames++;
}

bool capture_frame_should_end(capture_frame_T *capture_frame)
{
	return capture_frame->frames >= capture_frame->total_frames;
}

void capture_frame_unload(capture_frame_T *capture_frame)
{
	fclose(capture_frame->output_file);

	const char *call = writef(
			"ffmpeg -f rawvideo -pixel_format rgba -video_size %dx%d -framerate %d -i %s -c:v libx264 %s",
			capture_frame->width, capture_frame->height,
			capture_frame->fps,
			capture_frame->output_filepath, capture_frame->converted_filepath
	);
	system(call);

	free(capture_frame);
}
