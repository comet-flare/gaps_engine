#include <gapspch.hpp>
#include <Core/Event/Event.hpp>

namespace gaps
{
	EventId Event::GetId() const noexcept
	{
		return id;
	}

	Event::Event(EventId id) noexcept
		:
		id{ std::move(id) }
	{
	}

	void Event::OnCreate()
	{
	}

	void Event::OnRelease()
	{
	}
}