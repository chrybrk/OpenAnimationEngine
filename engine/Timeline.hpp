#pragma once

#include "Keyframe.hpp"

namespace OpenAnimationEngine {

	class Timeline {
		public:
			Timeline(float duration, bool reset);
			~Timeline();
			
			void Draw();
			void Update(float dt);

			inline void AddKeyframe(const Keyframe &keyframe) { m_Keyframes.push_back(keyframe); }
			inline float GetDuration() const { return m_Duration; }
			inline float GetCurrentTime() const { return m_CurrentTime; }
			inline void SetDuration(float duration) { m_Duration = duration; }
			inline std::vector<Keyframe> GetKeyframes() const { return m_Keyframes; }

			float GetMaxDurationOfKeyframe() const
			{
				float max = 0.0f;

				for (const Keyframe &keyframe : m_Keyframes)
					max = std::max(max, keyframe.end);

				return max;
			}

		private:
			float m_CurrentTime;
			float m_Duration;
			bool m_Reset;
			std::vector<Keyframe> m_Keyframes;
			bool m_PlayState;
	};

}
