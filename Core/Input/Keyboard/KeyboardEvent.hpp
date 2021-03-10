#pragma once

#include "../InputEvent.hpp"
#include "KeyCode.hpp"

namespace gaps
{
	class KeyboardEvent final : public InputEvent
	{
	public:
		explicit KeyboardEvent(EventId id) noexcept;

		struct Args final
		{
			KeyCode key = KeyCode::Unknown;
			KeyModifiers modifiers = KeyModifiers::None;
		} args;
	};
}