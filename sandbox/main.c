#include <stdio.h>
#include <stddef.h>
#include <raylib.h>
#include <raymath.h>
#include "OpenAnimationEngine.h"

/*
 * TODO 27-oct-2024: Array animation
*/

void color_interpolate(float t, animation_properties_T init_properties, animation_properties_T *end_properties)
{
	unsigned char r = Lerp(init_properties.color.r, end_properties->color.r, t);
	unsigned char g = Lerp(init_properties.color.g, end_properties->color.g, t);
	unsigned char b = Lerp(init_properties.color.b, end_properties->color.b, t);
	unsigned char a = Lerp(init_properties.color.a, end_properties->color.a, t);

	end_properties->color = (Color) { r, g, b, a };
}

int main(void)
{
	InitWindow(1200, 720, "Sandbox");
	SetTargetFPS(60);

	timeline_T *timeline = init_timeline(2.0f, true);

	animation_T *animation0 = init_animation();
	animation_push(animation0, 0.0f, 1.0f, (animation_properties_T) { .color = RAYWHITE }, color_interpolate);
	animation_push(animation0, 0.0f, 0.3f, (animation_properties_T) {  }, fade_in_animation);
	animation_push(animation0, 0.5f, 1.0f, (animation_properties_T) {  }, fade_out_animation);

	DEFER(text_destroy) object_T *tx0 = init_text("hey", 24.0f, animation0);

	timeline_add_keyframe(
		timeline,
		init_keyframe(
			0.0f,
			2.0f,
			(Vector2) { 100.0f, 200.0f },
			LIGHTGRAY,
			tx0
		)
	);

	while (!WindowShouldClose())
	{
		ClearBackground((Color) { 23, 23, 23, 255 });

		BeginDrawing();
		{
			timeline_draw(timeline);
			timeline_update(timeline, GetFrameTime());
		}
		EndDrawing();
	}

	return 0;
}
