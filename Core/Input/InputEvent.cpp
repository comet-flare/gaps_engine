#include <gapspch.hpp>
#include <Core/Input/InputEvent.hpp>

namespace gaps
{
	InputEvent::InputEvent() noexcept
		:
		Event{ EventId::Undefined }
	{
	}

	InputEvent::InputEvent(EventId id) noexcept
		:
		Event{ std::move(id) }
	{
	}
}