#include "OpenAnimationEngine.h"

timeline_T *timeline;
animation_T *text_animation;
object_T *text0;
capture_frame_T *capture_frame;

void init(void)
{
	timeline = init_timeline(10.0f, false);
	text_animation = init_animation();
	text0 = init_text("Hello, World!", 24.0f, text_animation);
	capture_frame = init_capture_frame("bin/output.raw", "bin/output.mp4", timeline_get_duration(timeline));

	animation_push(text_animation, 0.0f, 1.0f, (animation_properties_T) { .color = RED }, color_interpolation_animation);
	animation_push(text_animation, 0.0f, 0.3f, (animation_properties_T) { }, fade_in_animation);
	animation_push(text_animation, 0.8f, 1.0f, (animation_properties_T) { }, fade_out_animation);

	timeline_add_keyframe(timeline,
			init_keyframe(0.0f, 10.0f, (Vector2) { 100.0f, 200.0f }, LIGHTGRAY, text0)
	);
}

void uninit(void)
{
	free(timeline);
	text_destroy(&text0);
	capture_frame_unload(capture_frame);
}

void run(void)
{
	while (!WindowShouldClose() && !capture_frame_should_end(capture_frame))
	{
		ClearBackground((Color) { 23, 23, 23, 255 });
		BeginDrawing();
		{
			timeline_draw(timeline);
			timeline_update(timeline, GetFrameTime());
		}
		EndDrawing();

		capture_frame_push(capture_frame);
	}
}

application_properties_T init_application_properties = {
	.width = 1080,
	.height = 720,
	.fps = 30,
	.title = "Sandbox",
	.init = init,
	.uninit = uninit,
	.run = run
};
