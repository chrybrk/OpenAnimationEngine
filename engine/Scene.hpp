#pragma once

namespace OpenAnimationEngine {

	class Scene
	{
		public:
			virtual void OnLoad() = 0;
			virtual void OnTerminate() = 0;
			virtual void OnDraw(float dt) = 0;
	};

}
