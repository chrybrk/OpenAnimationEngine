#pragma once

#include "pch.hpp"

namespace OpenAnimationEngine {

	enum class AnimationKind
	{
		FadeIn,
		FadeOut,
		Move,
		Rotate,
		Resize,
		Scale
	};

	class Animation
	{
		public:
			typedef struct AnimationProperties
			{
				Vector2 position;
				Vector2 size;
				float rotation;
				float scale;
				Color color;
			} AnimationProperties;
		
		public:
			Animation();
			~Animation();

			void Push(AnimationKind animationKind, ...);
			void Pop();

			void Animate(float t, Vector2 *position, Vector2 *size, float *rotation, float *scale, Color *color);

		private:
			typedef struct AnimationStore {
				AnimationKind kind;

				float start;
				float end;

				Vector2 target;
				float scale;

				float (*ease)(float t, float b, float c, float d);
			} AnimationStore;

			std::vector<AnimationStore> m_Animations;
	};

}
