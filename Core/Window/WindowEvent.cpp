#include <gapspch.hpp>
#include <Core/Window/WindowEvent.hpp>
#include <Core/Debugger/Debug.hpp>

MOD("Core.Window.Event");

namespace gaps
{
	WindowEvent::WindowEvent() noexcept
		:
		Event{ EventId::Undefined }
	{
	}

	WindowEvent::WindowEvent(EventId id) noexcept
		:
		Event{ std::move(id) }
	{
		switch (id)
		{
		case gaps::EventId::WindowSizeChange:
			break;
		default:
			id = EventId::Undefined;
			DEBUG_WARN("EventId is not from WindowEvent family. It will be set to Undefined!");
			break;
		}
	}
}