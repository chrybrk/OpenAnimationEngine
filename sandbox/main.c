#include <stdio.h>
#include <stddef.h>
#include <raylib.h>
#include <raymath.h>
#include "OpenAnimationEngine.h"

int main(void)
{
	InitWindow(1200, 720, "Sandbox");
	SetTargetFPS(60);

	timeline_T *timeline = init_timeline(0.0f, true);

	DEFER(text_destroy) object_T *tx0 = init_text("hey", 24.0f);
	DEFER(text_destroy) object_T *tx1 = init_text("hey", 24.0f);

	animation_T *animation0 = init_animation(FADE_IN, LIGHTGRAY);
	animation_T *animation1 = init_animation(FADE_IN, LIGHTGRAY);

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

	timeline_add_keyframe(
		timeline,
		init_keyframe(
			0.0f,
			2.0f,
			(Vector2) { 200.0f, 200.0f },
			LIGHTGRAY,
			tx1
		)
	);

	while (!WindowShouldClose())
	{
		ClearBackground((Color) { 23, 23, 23, 255 });

		BeginDrawing();
		{
			timeline_draw(timeline);
		}
		EndDrawing();
	}

	return 0;
}
