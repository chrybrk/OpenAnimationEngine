#pragma once

#include "pch.hpp"
#include "Animation.hpp"

namespace OpenAnimationEngine {

	class Object
	{
		public:
			virtual void Draw(float t, Vector2 position, Color color) = 0;
	};

	class Text : public Object {
		public:
			Text(const std::string &text, float fontSize, const Animation &animation = Animation());
			~Text();

			void Draw(float t, Vector2 position, Color color);
			inline std::string GetText() const { return m_Text; }
			inline float GetFontSize() const { return m_FontSize; }
			inline Vector2 GetSize() const { return { (float)MeasureText(m_Text.c_str(), m_FontSize), m_FontSize }; }

			inline Animation *GetAnimation() { return &m_Animation; }
			inline void SetAnimation(const Animation &animation) { m_Animation = animation; }

		private:
			std::string m_Text;
			float m_FontSize;
			Animation m_Animation;
	};

}
