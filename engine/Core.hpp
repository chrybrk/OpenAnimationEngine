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

}
