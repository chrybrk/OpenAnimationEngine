#pragma once

#include "pch.hpp"

namespace OpenAnimationEngine {

	struct WindowProperties
	{
		std::string title;
		uint32_t width;
		uint32_t height;
		uint32_t fps;

		WindowProperties(const std::string &title = "OpenAnimationEngine", uint32_t width = 800, uint32_t height = 600, uint32_t fps = 60)
			: title(title), width(width), height(height), fps(fps)
		{
		}
	};

	class Window
	{
		public:
			static void Init(const WindowProperties &props = WindowProperties());
			static void Terminate();

			static void OnClear();
			static void SetClearColor(Color color);

			static Vector2 GetWindowSize() { return (Vector2) { (float)m_WindowData.Width, (float)m_WindowData.Height }; }
			static uint32_t GetWidth() { return m_WindowData.Width; }
			static uint32_t GetHeight() { return m_WindowData.Height; }

		private:
			struct WindowData
			{
				std::string Title;
				uint32_t Width;
				uint32_t Height;
				uint32_t FPS;
				Color color;
			};

		private:
			static WindowData m_WindowData;
	};

}
