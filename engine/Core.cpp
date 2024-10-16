#include "Core.hpp"

namespace OpenAnimationEngine {

	Vector2 GetPositionOnSurface(Alignment alignment, Vector2 surfaceSize, Vector2 objectSize, Vector2 gap)
	{
		switch (alignment)
		{
			case Alignment::TopLeft: return gap;
			case Alignment::TopRight: return { surfaceSize.x - (objectSize.x + gap.x), gap.y };
			case Alignment::BottomLeft: return { gap.x, surfaceSize.y - (objectSize.y + gap.y) };
			case Alignment::BottomRight: return { surfaceSize.x - (objectSize.x + gap.x), surfaceSize.y - (objectSize.y + gap.y) };
			case Alignment::Center: return { (surfaceSize.x / 2.0f) - (objectSize.x / 2.0f), (surfaceSize.y / 2.0f) - (objectSize.y / 2.0f) };
			case Alignment::Left: return { gap.x, (surfaceSize.y / 2.0f) - (objectSize.y / 2.0f) };
			case Alignment::Right: return { surfaceSize.x - (objectSize.x + gap.x), (surfaceSize.y / 2.0f) - (objectSize.y / 2.0f) };
			case Alignment::Top: return { (surfaceSize.x / 2.0f) - (objectSize.x / 2.0f), gap.y };
			case Alignment::Bottom: return { (surfaceSize.x / 2.0f) - (objectSize.x / 2.0f), surfaceSize.y - (objectSize.y + gap.y) };
		}
	}

	Vector2 GetPositionOnSubSurface(Alignment alignment, Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 objectSize, Vector2 gap)
	{
		return { 0, 0 };
	}

}
