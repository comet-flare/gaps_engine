#include <gapspch.hpp>
#include <Core/Time/TickEvent.hpp>

namespace gaps
{
	TickEvent::TickEvent() noexcept
		:
		Event{ EventId::Undefined }
	{
	}

	TickEvent::TickEvent(const EventId id) noexcept
		:
		Event{ id }
	{
	}
}