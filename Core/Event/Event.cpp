#include <gapspch.hpp>
#include <Core/Event/Event.hpp>

namespace gaps
{
	EventId Event::GetId() const noexcept
	{
		return id;
	}

	Event::Event(const EventId id) noexcept
		:
		id{ id }
	{
	}

	void Event::OnCreate()
	{
	}

	void Event::OnRelease()
	{
	}
}