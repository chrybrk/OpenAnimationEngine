#include "Application.hpp"
#include "Window.hpp"

namespace OpenAnimationEngine {

	Application::Application()
	{
		Window::Init();
	}

	Application::~Application()
	{
		for (Scene *scene : m_Scenes) scene->OnTerminate();
	}

	void Application::PushScene(Scene *scene)
	{
		m_Scenes.push_back(scene);
		scene->OnLoad();
	}

	void Application::Run()
	{
		while (!WindowShouldClose())
		{
			Window::OnClear();

			float dt = GetFrameTime();

			BeginDrawing();
			{
				for (Scene *scene : m_Scenes) scene->OnDraw(dt);
			}
			EndDrawing();
		}
	}

}
