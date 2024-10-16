#include "OpenAnimationEngine.hpp"

class ArrayAnimation : public OpenAnimationEngine::Scene {
	public:
		ArrayAnimation()
			: m_Timeline(8.0f, true)
		{
		}

		void OnLoad() override
		{
			OpenAnimationEngine::ref<OpenAnimationEngine::Text> tx0 = OpenAnimationEngine::makeref<OpenAnimationEngine::Text>("Hey, Sexy! :)", 48.0f);
			tx0->GetAnimation()->Push(OpenAnimationEngine::AnimationKind::FadeIn, 0.0f, 0.2f);
			tx0->GetAnimation()->Push(OpenAnimationEngine::AnimationKind::FadeOut, 0.8f, 1.0f);

			OpenAnimationEngine::ref<OpenAnimationEngine::Text> tx1 = OpenAnimationEngine::makeref<OpenAnimationEngine::Text>("Wanna", 48.0f, *tx0->GetAnimation());
			OpenAnimationEngine::ref<OpenAnimationEngine::Text> tx2 = OpenAnimationEngine::makeref<OpenAnimationEngine::Text>("Go", 48.0f, *tx0->GetAnimation());
			OpenAnimationEngine::ref<OpenAnimationEngine::Text> tx3 = OpenAnimationEngine::makeref<OpenAnimationEngine::Text>("Out?", 48.0f, *tx0->GetAnimation());
			OpenAnimationEngine::ref<OpenAnimationEngine::Text> tx4 = OpenAnimationEngine::makeref<OpenAnimationEngine::Text>("Yes or Yes?", 48.0f, *tx0->GetAnimation());
			OpenAnimationEngine::ref<OpenAnimationEngine::Text> tx5 = OpenAnimationEngine::makeref<OpenAnimationEngine::Text>("I'm glad you took `yes`.", 48.0f, *tx0->GetAnimation());

			m_Timeline.AddKeyframe(
				OpenAnimationEngine::Keyframe(
					tx0,
					0.0f, 2.0f,
					OpenAnimationEngine::GetPositionOnSurface(OpenAnimationEngine::Alignment::Center, OpenAnimationEngine::Window::GetWindowSize(), tx0->GetSize(), { 0.0f, 0.0f }),
					LIGHTGRAY
				)
			);

			m_Timeline.AddKeyframe(
				OpenAnimationEngine::Keyframe(
					tx1,
					1.5f, 3.5f,
					OpenAnimationEngine::GetPositionOnSurface(OpenAnimationEngine::Alignment::Center, OpenAnimationEngine::Window::GetWindowSize(), tx1->GetSize(), { 0.0f, 0.0f }),
					LIGHTGRAY
				)
			);

			m_Timeline.AddKeyframe(
				OpenAnimationEngine::Keyframe(
					tx2,
					3.0f, 5.0f,
					OpenAnimationEngine::GetPositionOnSurface(OpenAnimationEngine::Alignment::Center, OpenAnimationEngine::Window::GetWindowSize(), tx2->GetSize(), { 0.0f, 0.0f }),
					LIGHTGRAY
				)
			);

			m_Timeline.AddKeyframe(
				OpenAnimationEngine::Keyframe(
					tx3,
					4.5f, 6.5f,
					OpenAnimationEngine::GetPositionOnSurface(OpenAnimationEngine::Alignment::Center, OpenAnimationEngine::Window::GetWindowSize(), tx3->GetSize(), { 0.0f, 0.0f }),
					LIGHTGRAY
				)
			);

			m_Timeline.AddKeyframe(
				OpenAnimationEngine::Keyframe(
					tx4,
					6.0f, 8.0f,
					OpenAnimationEngine::GetPositionOnSurface(OpenAnimationEngine::Alignment::Center, OpenAnimationEngine::Window::GetWindowSize(), tx4->GetSize(), { 0.0f, 0.0f }),
					LIGHTGRAY
				)
			);

			m_Timeline.AddKeyframe(
				OpenAnimationEngine::Keyframe(
					tx5,
					7.5f, 9.5f,
					OpenAnimationEngine::GetPositionOnSurface(OpenAnimationEngine::Alignment::Center, OpenAnimationEngine::Window::GetWindowSize(), tx5->GetSize(), { 0.0f, 0.0f }),
					LIGHTGRAY
				)
			);

			float max = m_Timeline.GetMaxDurationOfKeyframe();
			m_Timeline.SetDuration(max);
		}

		void OnTerminate() override
		{
		}

		void OnDraw(float dt) override
		{
			m_Timeline.Draw();
			m_Timeline.Update(dt);
		}

	private:
		OpenAnimationEngine::Timeline m_Timeline;
};

class Sandbox : public OpenAnimationEngine::Application {
	public:
		Sandbox()
		{
			SetWindowPosition(100.0f, 100.0f);
			OpenAnimationEngine::Window::SetClearColor((Color) { 23, 23, 23, 255 });
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
