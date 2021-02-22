#pragma once

#include "MouseButton.hpp"

namespace gaps
{
	class Mouse final
	{
	public:
		float GetXPosition() const noexcept;
		float GetYPosition() const noexcept;
		bool IsButtonDown(MouseButton button) const;

	private:
		bool HandleButtonPress(MouseButton button, float xPosition, float yPosition);
		bool HandleButtonRelease(MouseButton button, float xPosition, float yPosition);
		bool HandleMotion(float xPosition, float yPosition);
		bool HandleRelativeMotion(float xPosition, float yPosition);
		bool HandleScroll(float xScroll, float yScroll, float xPosition, float yPosition);

		float xPosition = 0.f;
		float yPosition = 0.f;
		bool bButtonStates[static_cast<uint32_t>(MouseButton::Count)]{ false };

		friend class Input;
		friend class InternalEvents;
	};
}