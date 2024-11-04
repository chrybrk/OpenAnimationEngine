#include "OpenAnimationEngine.h"

timeline_T *timeline;
capture_frame_T *capture_frame;

void introduction_scene()
{
	list_T *keyframes = init_list(sizeof(keyframe_T*));

	animation_T *fader = init_animation();
	animation_push(fader, 0.0f, 0.2f, (animation_properties_T) {  }, fade_in_animation);
	animation_push(fader, 0.8f, 1.0f, (animation_properties_T) {  }, fade_out_animation);

	object_T *t0 = init_text("Episode - 1", 40.0f, fader);
	object_T *t1 = init_text("Introduction", 48.0f, fader);
	object_T *t2 = init_text("Array", 40.0f, fader);
	object_T *t3 = init_text("Array are linear data-structure, \n\nthey store same kind of elements \n\nand has fixed size.", 24.0f, fader);
	object_T *a0 = init_array(
			5, (int[]) { 10, 20, 30, 40, 50 }, (Vector2) { 500.0f, 50.0f }, (Vector2) { 5.0f, 0.0f }, 24.0f, LIGHTGRAY, fader, fader
	);
	object_T *t4 = init_text("Contagious memory location", 24.0f, fader);

	Vector2 center_alignment = get_alignment_on_surface(center, application_instance->size, Vector2Zero(), Vector2Zero());
	Vector2 top_alignment = get_alignment_on_surface(top, application_instance->size, Vector2Zero(), Vector2Zero());

	list_push(keyframes,
			init_keyframe(0.0f, 2.0f, offset_alignment(center_alignment, text_get_size(t0), 0.0f, 25.0f), LIGHTGRAY, t0)
	);

	list_push(keyframes,
			init_keyframe(1.5f, 4.0f, offset_alignment(center_alignment, text_get_size(t1), 0.0f, 0.0f), LIGHTGRAY, t1)
	);

	list_push(keyframes,
			init_keyframe(1.5f, 4.0f, offset_alignment(center_alignment, text_get_size(t2), 0.0f, 50.0f), LIGHTGRAY, t2)
	);

	list_push(keyframes,
			init_keyframe(4.0f, 15.0f, offset_alignment(center_alignment, array_get_size(a0), 0.0f, 0.0f), BLACK, a0)
	);

	list_push(keyframes,
			init_keyframe(4.0f, 15.0f, offset_alignment(top_alignment, text_get_size(t1), 0.0f, 100.0f), LIGHTGRAY, t1)
	);

	list_push(keyframes,
			init_keyframe(4.0f, 15.0f, offset_alignment(top_alignment, text_get_size(t3), 0.0f, 200.0f), LIGHTGRAY, t3)
	);

	list_push(keyframes,
			init_keyframe(4.0f, 15.0f, offset_alignment(center_alignment, text_get_size(t4), 0.0f, 50.0f), LIGHTGRAY, t4)
	);

	foreach(keyframe_T *item, list_iterator(keyframes), {
			timeline_add_keyframe(timeline, item);
	});
}

void introduction_creation_scene()
{
	list_T *keyframes = init_list(sizeof(keyframe_T*));

	animation_T *fader = init_animation();
	animation_push(fader, 0.0f, 0.2f, (animation_properties_T) {  }, fade_in_animation);
	animation_push(fader, 0.8f, 1.0f, (animation_properties_T) {  }, fade_out_animation);
	animation_push(fader, 0.2f, 0.4f, (animation_properties_T) { .i1 = 0 }, array_animation);
	animation_push(fader, 0.3f, 0.5f, (animation_properties_T) { .i1 = 1 }, array_animation);
	animation_push(fader, 0.4f, 0.6f, (animation_properties_T) { .i1 = 2 }, array_animation);
	animation_push(fader, 0.5f, 0.7f, (animation_properties_T) { .i1 = 3 }, array_animation);
	animation_push(fader, 0.6f, 0.8f, (animation_properties_T) { .i1 = 4 }, array_animation);

	object_T *t0 = init_text("Introduction: Creation", 48.0f, fader);
	object_T *t1 = init_text("In java we can create array with different methods: ", 24.0f, fader);
	object_T *t2 = init_text("int[] array = { 1, 2, 3, 4, 5 };", 24.0f, fader);
	object_T *t3 = init_text("int[] array = new int[5];", 24.0f, fader);
	object_T *t4 = init_text("Looping through each element", 24.0f, fader);
	object_T *t5 = init_text("for (int i = 0; i < 5; ++i){\n\n\tSystem.out.println(array[i]);\n\n}", 24.0f, fader);
	object_T *a0 = init_array(
			5, (int[]) { 1, 2, 3, 4, 5 }, (Vector2) { 500.0f, 50.0f }, (Vector2) { 5.0f, 0.0f }, 24.0f, LIGHTGRAY, fader, fader
	);

	Vector2 center_alignment = get_alignment_on_surface(center, application_instance->size, Vector2Zero(), Vector2Zero());
	Vector2 top_alignment = get_alignment_on_surface(top, application_instance->size, Vector2Zero(), Vector2Zero());
	Vector2 top_left_alignment = get_alignment_on_surface(tleft, application_instance->size, Vector2Zero(), Vector2Zero());

	list_push(keyframes,
			init_keyframe(15.0f, 17.0f, offset_alignment(center_alignment, text_get_size(t0), 0.0f, 0.0f), LIGHTGRAY, t0)
	);

	list_push(keyframes,
			init_keyframe(16.5f, 25.0f, offset_alignment(top_alignment, text_get_size(t0), 0.0f, 100.0f), LIGHTGRAY, t0)
	);

	list_push(keyframes,
			init_keyframe(16.5f, 25.0f, offset_alignment_adj(left, top_left_alignment, text_get_size(t1), 150.0f, 200.0f), LIGHTGRAY, t1)
	);

	list_push(keyframes,
			init_keyframe(16.5f, 25.0f, offset_alignment_adj(left, top_left_alignment, text_get_size(t2), 200.0f, 250.0f), LIGHTGRAY, t2)
	);

	list_push(keyframes,
			init_keyframe(16.5f, 25.0f, offset_alignment_adj(left, top_left_alignment, text_get_size(t3), 200.0f, 280.0f), LIGHTGRAY, t3)
	);

	list_push(keyframes,
			init_keyframe(16.5f, 25.0f, offset_alignment(center_alignment, array_get_size(a0), 0.0f, 0.0f), BLACK, a0)
	);

	list_push(keyframes,
			init_keyframe(16.5f, 25.0f, offset_alignment(center_alignment, text_get_size(t4), 0.0f, 50.0f), LIGHTGRAY, t4)
	);

	list_push(keyframes,
			init_keyframe(16.5f, 25.0f, offset_alignment(center_alignment, text_get_size(t5), 0.0f, 150.0f), LIGHTGRAY, t5)
	);

	foreach(keyframe_T *item, list_iterator(keyframes), {
			timeline_add_keyframe(timeline, item);
	});
}

void ending_scene()
{
	list_T *keyframes = init_list(sizeof(keyframe_T*));

	animation_T *fader = init_animation();
	animation_push(fader, 0.0f, 0.2f, (animation_properties_T) {  }, fade_in_animation);
	animation_push(fader, 0.8f, 1.0f, (animation_properties_T) {  }, fade_out_animation);

	object_T *t0 = init_text("Thank you!", 48.0f, fader);

	Vector2 center_alignment = get_alignment_on_surface(center, application_instance->size, Vector2Zero(), Vector2Zero());

	list_push(keyframes,
			init_keyframe(25.0f, 30.0f, offset_alignment(center_alignment, text_get_size(t0), 0.0f, 0.0f), LIGHTGRAY, t0)
	);

	foreach(keyframe_T *item, list_iterator(keyframes), {
			timeline_add_keyframe(timeline, item);
	});
}

void init(void)
{
	timeline = init_timeline(0.0f, true);

	introduction_scene();
	introduction_creation_scene();
	ending_scene();

	float max_duration = timeline_get_max_duration_from_keyframe(timeline);
	timeline_set_duration(timeline, max_duration);
	capture_frame = init_capture_frame("bin/output.raw", "bin/output.mp4", max_duration);
}

void uninit(void)
{
	free(timeline);
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
	.size = (Vector2) { 1920, 1080 },
	.fps = 30,
	.title = "Sandbox",
	.init = init,
	.uninit = uninit,
	.run = run
};
