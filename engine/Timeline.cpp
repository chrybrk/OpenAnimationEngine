#include "Timeline.hpp"

namespace OpenAnimationEngine {

	Timeline::Timeline(float duration, bool reset)
		: m_CurrentTime(0.0f), m_Duration(duration), m_Reset(reset), m_PlayState(true)
	{
	}

	Timeline::~Timeline()
	{
	}
	
	void Timeline::Draw()
	{
		for (const Keyframe &keyframe : m_Keyframes)
		{
			if (m_CurrentTime >= keyframe.start && m_CurrentTime <= keyframe.end)
				keyframe.object->Draw((m_CurrentTime - keyframe.start) / (keyframe.end - keyframe.start), keyframe.position, keyframe.color);
		}
	}

	void Timeline::Update(float dt)
	{
		if (m_CurrentTime >= m_Duration)
		{
			if (m_Reset) m_CurrentTime = 0.0f;
		}
		else
		{
			if (m_PlayState) m_CurrentTime += dt;
		}

		// TODO: add timeline key controls.
	}

}
