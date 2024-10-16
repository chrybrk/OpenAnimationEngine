#include "Object.hpp"

namespace OpenAnimationEngine {

	Text::Text(const std::string &text, float fontSize, const Animation &animation)
		: m_Text(text), m_FontSize(fontSize), m_Animation(animation)
	{
	}

	Text::~Text()
	{
	}

	void Text::Draw(float t, Vector2 position, Color color)
	{
		m_Animation.Animate(t, &position, nullptr, nullptr, &m_FontSize, &color);
		DrawText(m_Text.c_str(), position.x, position.y, m_FontSize, color);
	}

}
