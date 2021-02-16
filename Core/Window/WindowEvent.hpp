#pragma once

#include "../Event/Event.hpp"

namespace gaps
{
	class Window;

	class WindowEvent final : public Event
	{
	public:
		WindowEvent() noexcept;
		explicit WindowEvent(EventId id) noexcept;

		struct Args final
		{
			uint32_t width = 0u;
			uint32_t height = 0u;
		} args;

		Window* pWindow = nullptr;
	};
}