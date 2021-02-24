#include <gapspch.hpp>
#include <Core/Time/TickEvent.hpp>

namespace gaps
{
	TickEvent::TickEvent() noexcept
		:
		Event{ EventId::Undefined }
	{
	}

	TickEvent::TickEvent(EventId id) noexcept
		:
		Event{ std::move(id) }
	{
	}
}