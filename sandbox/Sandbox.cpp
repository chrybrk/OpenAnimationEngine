#include "OpenAnimationEngine.hpp"

class ArrayAnimation : public OpenAnimationEngine::Scene {
	public:
		ArrayAnimation()
		{
		}

		void OnLoad() override
		{
		}

		void OnTerminate() override
		{
		}

		void OnDraw(float dt) override
		{
			DrawRectangle(100, 100, 100, 100, RED);
		}

	private:
};

class Sandbox : public OpenAnimationEngine::Application {
	public:
		Sandbox()
		{
			SetWindowPosition(100.0f, 100.0f);
			PushScene(new ArrayAnimation());
		}

		~Sandbox()
		{
		}
};

OpenAnimationEngine::Application *OpenAnimationEngine::CreateApplication()
{
	Sandbox *app = new Sandbox();
	return app;
}
