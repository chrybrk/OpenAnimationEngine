#ifndef __entry_point__
#define __entry_point__

extern application_properties_T init_application_properties;
application_properties_T *application_instance;

int main(int argc, char **argv)
{
	application_instance = &init_application_properties;

	InitWindow(
		init_application_properties.size.x,
		init_application_properties.size.y,
		init_application_properties.title
	);
	SetTargetFPS(init_application_properties.fps);

	init_application_properties.init();

	init_application_properties.run();
	
	init_application_properties.uninit();
	CloseWindow();

	return 0;
}

#endif // __entry_point__
