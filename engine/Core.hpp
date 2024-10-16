#pragma once

#include "pch.hpp"

namespace OpenAnimationEngine {

	template<typename T>
	using unqptr = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr unqptr<T> makeunique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr ref<T> makeref(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	enum class Alignment
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		Center,
		Left,
		Right,
		Top,
		Bottom
	};

	Vector2 GetPositionOnSurface(Alignment alignment, Vector2 surfaceSize, Vector2 objectSize, Vector2 gap);
	Vector2 GetPositionOnSubSurface(Alignment alignment, Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 objectSize, Vector2 gap);

}
