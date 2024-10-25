#include "OpenAnimationEngine.hpp"

class TestScene : public OpenAnimationEngine::Scene
{
	public:
		TestScene()
			: m_Timeline(2.0f, true)
		{
			m_Font = LoadFontEx("assets/Mathics Round Free.ttf", 148, nullptr, 0);
			// SetTextureFilter(m_Font.texture, TEXTURE_FILTER_TRILINEAR);
		}

		void OnLoad() override
		{
			/*
			OpenAnimationEngine::ref<OpenAnimationEngine::Array> arr0 = 
				OpenAnimationEngine::makeref<OpenAnimationEngine::Array>(
						(std::vector<int>){ 10, 20, 30, 40, 50 },
						500.0f,
						50.0f,
						5.0f,
						24.0f,
						LIGHTGRAY
				);

			// arr0->GetBackgroundAnimation()->Push(OpenAnimationEngine::AnimationKind::FadeIn, 0.0f, 0.3f);
			// arr0->GetBackgroundAnimation()->Push(OpenAnimationEngine::AnimationKind::FadeOut, 0.8f, 1.0f);
			arr0->SetShowIndex(true);

			m_Timeline.AddKeyframe(
					OpenAnimationEngine::Keyframe(
						arr0,
						0.0f,
						2.0f,
						OpenAnimationEngine::GetPositionOnSurface(OpenAnimationEngine::Alignment::Center, OpenAnimationEngine::Window::GetWindowSize(), arr0->GetArrayDrawSize(), { 0.0f, 0.0f }),
						BLACK
					)
			);
			*/

			OpenAnimationEngine::ref<OpenAnimationEngine::Text> tx0 = OpenAnimationEngine::makeref<OpenAnimationEngine::Text>("Presentation On Array", 54.0f);
			OpenAnimationEngine::ref<OpenAnimationEngine::Text> tx1 = OpenAnimationEngine::makeref<OpenAnimationEngine::Text>("Name: Rahul Chauhan", 24.0f);
			OpenAnimationEngine::ref<OpenAnimationEngine::Text> tx2 = OpenAnimationEngine::makeref<OpenAnimationEngine::Text>("Roll No: 202210101310142", 24.0f);
			OpenAnimationEngine::ref<OpenAnimationEngine::Text> tx3 = OpenAnimationEngine::makeref<OpenAnimationEngine::Text>("Cource: BCA (5C)", 24.0f);

			tx0->SetFont(m_Font);
			tx1->SetFont(m_Font);
			tx2->SetFont(m_Font);
			tx3->SetFont(m_Font);

			Vector2 titlePosition = OpenAnimationEngine::GetPositionOnSurface(OpenAnimationEngine::Alignment::Top, OpenAnimationEngine::Window::GetWindowSize(), tx0->GetSize(), { 0.0f, 100.0f });
			Vector2 centerPosition = OpenAnimationEngine::GetPositionOnSurface(OpenAnimationEngine::Alignment::Center, OpenAnimationEngine::Window::GetWindowSize(), tx1->GetSize(), { 0.0f, 100.0f });

			m_Timeline.AddKeyframe(
				OpenAnimationEngine::Keyframe(
					tx0,
					0.0f, 2.5f,
					titlePosition,
					LIGHTGRAY
				)
			);

			size_t index = 0;
			for (auto item : std::vector<OpenAnimationEngine::ref<OpenAnimationEngine::Text>>({ tx1, tx2, tx3 }))
			{
				m_Timeline.AddKeyframe(
					OpenAnimationEngine::Keyframe(
						item,
						0.0f, 2.5f,
						{ centerPosition.x - 50.0f, centerPosition.y + (index * 30.0f) },
						LIGHTGRAY
					)
				);

				index++;
			}

			m_Timeline.SetDuration(m_Timeline.GetMaxDurationOfKeyframe() - .5f);
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
		Font m_Font;
};

class Sandbox : public OpenAnimationEngine::Application
{
	public:
		Sandbox()
		{
			SetWindowPosition(100.0f, 100.0f);
			OpenAnimationEngine::Window::SetClearColor((Color) { 23, 23, 23, 255 });
			PushScene(new TestScene());
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
