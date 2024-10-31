#include "OpenAnimationEngine.h"

timeline_T *timeline;

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
			init_keyframe(4.0f, 8.0f, offset_alignment(center_alignment, array_get_size(a0), 0.0f, 0.0f), BLACK, a0)
	);

	list_push(keyframes,
			init_keyframe(4.0f, 8.0f, offset_alignment(top_alignment, text_get_size(t1), 0.0f, 100.0f), LIGHTGRAY, t1)
	);

	list_push(keyframes,
			init_keyframe(4.0f, 8.0f, offset_alignment(top_alignment, text_get_size(t3), 0.0f, 200.0f), LIGHTGRAY, t3)
	);

	foreach(keyframe_T *item, list_iterator(keyframes), {
			timeline_add_keyframe(timeline, item);
	});
}

void init(void)
{
	timeline = init_timeline(0.0f, true);

	introduction_scene();

	timeline_set_duration(timeline, timeline_get_max_duration_from_keyframe(timeline));
}

void uninit(void)
{
	free(timeline);
}

void DrawArrow(Vector2 start, Vector2 end, float size, Color color)
{
    // Draw the main line
    DrawLineV(start, end, color);

    // Calculate direction vector
    Vector2 direction = Vector2Normalize(Vector2Subtract(end, start));

    // Calculate the arrowhead points
    Vector2 leftWing = Vector2Subtract(end, Vector2Scale(Vector2Rotate(direction, PI / 6), size));
    Vector2 rightWing = Vector2Subtract(end, Vector2Scale(Vector2Rotate(direction, -PI / 6), size));

    // Draw the arrowhead
    DrawLineV(end, leftWing, color);
    DrawLineV(end, rightWing, color);
}

void DrawBezierCurve(Vector2 start, Vector2 control, Vector2 end, int segments, Color color)
{
    Vector2 previous = start;

    for (int i = 1; i <= segments; i++)
    {
        float t = (float)i / segments;
        float invT = 1 - t;

        // Quadratic Bézier formula
        Vector2 point = {
            invT * invT * start.x + 2 * invT * t * control.x + t * t * end.x,
            invT * invT * start.y + 2 * invT * t * control.y + t * t * end.y
        };

        DrawLineV(previous, point, color);
        previous = point;
    }
}

// Function to draw an arrow line with optional curve and customizable arrowhead angle
void DrawArrowLine(Vector2 start, Vector2 target, float arrowSize, float arrowAngle, bool isCurved, Color color)
{
    // Calculate distance and angle between start and target
    Vector2 direction = Vector2Subtract(target, start);
    float distance = Vector2Length(direction);
    float angle = atan2f(direction.y, direction.x);

    // Draw line (either straight or curved)
    if (isCurved)
    {
        // Curved line (quadratic Bezier curve with control point in between start and target)
        Vector2 controlPoint = { (start.x + target.x) / 2, (start.y + target.y) / 2 - distance / 4 };
        int segments = 20;
        
        Vector2 previous = start;
        for (int i = 1; i <= segments; i++)
        {
            float t = (float)i / segments;
            float invT = 1.0f - t;

            Vector2 point = {
                invT * invT * start.x + 2 * invT * t * controlPoint.x + t * t * target.x,
                invT * invT * start.y + 2 * invT * t * controlPoint.y + t * t * target.y
            };

            DrawLineV(previous, point, color);
            previous = point;
        }
    }
    else
    {
        // Straight line
        DrawLineV(start, target, color);
    }

    // Draw the arrowhead with customizable angle
    Vector2 arrowDirection = Vector2Normalize(Vector2Subtract(target, start));
    Vector2 leftWing = Vector2Subtract(target, Vector2Scale(Vector2Rotate(arrowDirection, arrowAngle), arrowSize));
    Vector2 rightWing = Vector2Subtract(target, Vector2Scale(Vector2Rotate(arrowDirection, -arrowAngle), arrowSize));

    DrawLineV(target, leftWing, color);
    DrawLineV(target, rightWing, color);
}
void run(void)
{
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
}

application_properties_T init_application_properties = {
	.size = (Vector2) { 1200, 720 },
	.fps = 30,
	.title = "Sandbox",
	.init = init,
	.uninit = uninit,
	.run = run
};
