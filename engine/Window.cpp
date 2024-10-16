#include "Window.hpp"

namespace OpenAnimationEngine {

	Window::WindowData Window::m_WindowData;

	void Window::Init(const WindowProperties &props)
	{
		m_WindowData.Title = props.title;
		m_WindowData.Width = props.width;
		m_WindowData.Height = props.height;
		m_WindowData.FPS = props.fps;
		m_WindowData.color = RAYWHITE;

		InitWindow(m_WindowData.Width, m_WindowData.Height, m_WindowData.Title.c_str());
		SetTargetFPS(m_WindowData.FPS);
	}

	void Window::Terminate()
	{
		CloseWindow();
	}

	void Window::OnClear()
	{
		ClearBackground(m_WindowData.color);
	}

	void Window::SetClearColor(Color color)
	{
		m_WindowData.color = color;
	}

}
