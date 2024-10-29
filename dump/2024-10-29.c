#include <stdio.h>
#include <stddef.h>
#include <raylib.h>
#include <raymath.h>
#include "OpenAnimationEngine.h"

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

		DrawText(text, rel_position.x + element_size.x / 2 - text_width / 2 - array->gap.x, rel_position.y + element_size.y / 2 - array->fontSize / 2, array->fontSize, color);
	}
}

object_T *init_array(size_t size, int elements[size], Vector2 dsize, Vector2 gap, float fontSize, Color bg_color, animation_T *bg_animation, animation_T *fg_animation)
{
	array_T *array = malloc(sizeof(struct ARRAY_STRUCT));
	array->base.draw = draw_array;
	array->size = size;
	array->elements = elements;
	array->dsize = dsize;
	array->gap = gap;
	array->fontSize = fontSize;
	array->bg_color = bg_color;
	array->bg_animation = bg_animation;
	array->fg_animation = fg_animation;
	return (object_T*)array;
}

void array_destroy(object_T **object)
{
	array_T *array = (array_T*)(*object) - offsetof(array_T, base);
	if (array)
		free(array);
}

static int WINDOW_WIDTH 	= 800;
static int WINDOW_HEIGHT 	= 450;
static int WINDOW_FPS 		= 30;

int main(void)
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sandbox");
	SetTargetFPS(WINDOW_FPS);

	timeline_T *timeline = init_timeline(10.0f, false);

  FILE *file = fopen("bin/output_video.raw", "wb");
	if (!file)
	{
		perror("Failed to open file for writing.\n");
		CloseWindow();
		return -1;
	}

	const int totalFrames = (int)(timeline_get_duration(timeline) * WINDOW_FPS);
	const int frameDataSize = WINDOW_WIDTH * WINDOW_HEIGHT * 4; // RGBA format

	animation_T *animation0 = init_animation();
	animation_push(animation0, 0.0f, 0.5f, (animation_properties_T) {  }, fade_in_animation);
	animation_push(animation0, 0.5f, 1.0f, (animation_properties_T) {  }, fade_out_animation);
	animation_push(animation0, 0.0f, 0.2f, (animation_properties_T) { .v2 = { 100.0f, 200.0f } }, move_animation);
	animation_push(animation0, 0.8f, 1.0f, (animation_properties_T) { .v2 = { 100.0f, 400.0f } }, move_animation);

	DEFER(array_destroy) object_T *arr0 = init_array(5, (int[]){ 1, 2, 3, 4, 5 }, (Vector2) { 400.0f, 40.0f }, (Vector2) { 5.0f, 0.0f }, 24.0f, LIGHTGRAY, animation0, animation0);

	timeline_add_keyframe(
		timeline,
		init_keyframe(
			0.0f,
			2.0f,
			(Vector2) { 100.0f, 0.0f },
			BLACK,
			arr0
		)
	);

	int frameCount = 0;
	while (!WindowShouldClose() && frameCount < totalFrames)
	{
		ClearBackground((Color) { 23, 23, 23, 255 });

		BeginDrawing();
		{
			timeline_draw(timeline);
			timeline_update(timeline, GetFrameTime());
		}
		EndDrawing();

		Image image = LoadImageFromScreen();
		fwrite(image.data, 1, frameDataSize, file);
		UnloadImage(image); // Free the frame data from memory

		frameCount++;
	}

	fclose(file);
	CloseWindow();

	return 0;
}
