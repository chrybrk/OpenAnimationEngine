#pragma once

#include "pch.hpp"
#include "Scene.hpp"

namespace OpenAnimationEngine {

	class Application
	{
		public:
			Application();
			virtual ~Application();
			
			void PushScene(Scene *scene);
			void Run();

		private:
			std::vector<Scene*> m_Scenes;
	};

	Application *CreateApplication();

}
