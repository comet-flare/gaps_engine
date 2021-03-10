#include <gapspch.hpp>
#include <Core/Input/InputEvent.hpp>

namespace gaps
{
	InputEvent::InputEvent() noexcept
		:
		Event{ EventId::Undefined }
	{
	}

	InputEvent::InputEvent(const EventId id) noexcept
		:
		Event{ id }
	{
	}
}