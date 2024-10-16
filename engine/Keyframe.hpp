#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Object.hpp"

namespace OpenAnimationEngine {

	typedef struct Keyframe
	{
		ref<Object> object;
		float start;
		float end;
		Vector2 position;
		Color color;

		Keyframe(const ref<Object> &object, float start, float end, const Vector2 position, Color color)
			: object(object), start(start), end(end), position(position), color(color)
		{}
	} Keyframe;

}
