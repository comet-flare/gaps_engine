#pragma once

#include "../InputEvent.hpp"
#include "MouseButton.hpp"

namespace gaps
{
	class MouseEvent final : public InputEvent
	{
	public:
		explicit MouseEvent(EventId id) noexcept;

		struct Args final
		{
			MouseButton button = MouseButton::Unknown;
			float xDifference = 0.f;
			float yDifference = 0.f;
			float xPosition = 0.f;
			float yPosition = 0.f;
			float xScroll = 0.f;
			float yScroll = 0.f;
			bool bRelativeMotion = false;
		} args;
	};
}