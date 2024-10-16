#pragma once

extern OpenAnimationEngine::Application *OpenAnimationEngine::CreateApplication();

int main(int argc, char** argv)
{
	OpenAnimationEngine::Application *app = OpenAnimationEngine::CreateApplication();
	app->Run();

	delete app;
}
