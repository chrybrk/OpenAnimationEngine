#include "Animation.hpp"

namespace OpenAnimationEngine {

	Animation::Animation()
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Push(AnimationKind kind, ...)
	{
		va_list args;
		va_start(args, kind);

		AnimationStore store;

		store.kind = kind;
		store.start = (float)va_arg(args, double);
		store.end = (float)va_arg(args, double);

		switch (kind)
		{
			case AnimationKind::FadeIn:
			case AnimationKind::FadeOut: break;
			case AnimationKind::Move:
			{
				store.target = va_arg(args, Vector2);
				store.ease = va_arg(args, float(*)(float, float, float, float));
				break;
			}
			case AnimationKind::Rotate:
			case AnimationKind::Scale:
			{
				store.scale = (float)va_arg(args, double);
				store.ease = va_arg(args, float(*)(float, float, float, float));
				break;
			}
			case AnimationKind::Resize:
			{
				store.target = va_arg(args, Vector2);
				store.ease = va_arg(args, float(*)(float, float, float, float));
				break;
			}
		}

		m_Animations.push_back(store);
		va_end(args);
	}

	void Animation::Animate(float t, Vector2 *position, Vector2 *size, float *rotation, float *scale, Color *color)
	{
		for (const AnimationStore &animation : m_Animations)
		{
			if (animation.start <= t)
			{
				float ft = (t - animation.start) / (animation.end - animation.start);
				switch (animation.kind)
				{
					case AnimationKind::FadeIn: *color = Fade(*color, ft); break;
					case AnimationKind::FadeOut: *color = Fade(*color,  1.0f - ft); break;
					case AnimationKind::Move: *position = Vector2MoveTowards(*position, animation.target, Vector2Distance(*position, animation.target) * animation.ease(ft, 0.0f, 1.0f, animation.end)); break;
					case AnimationKind::Rotate: *rotation = Lerp(*rotation, animation.scale, animation.ease(ft, 0.0f, 1.0f, animation.end)); break;
					case AnimationKind::Scale: *scale = Lerp(*scale, animation.scale, animation.ease(ft, 0.0f, 1.0f, animation.end)); break;
					case AnimationKind::Resize: *size = Vector2MoveTowards(*size, animation.target, Vector2Distance(*size, animation.target) * animation.ease(ft, 0.0f, 1.0f, animation.end)); break;
				}
			}
		}
	}

}
