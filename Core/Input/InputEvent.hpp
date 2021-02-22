#pragma once

#include "../Event/Event.hpp"

namespace gaps
{
	class InputEvent : public Event
	{
	public:
		InputEvent() noexcept;
		explicit InputEvent(EventId id) noexcept;
	};

	struct InputEventQueue final
	{
		using EventType = std::pair<std::promise<bool>, std::unique_ptr<InputEvent>>;

		std::queue<EventType> queue;
		std::mutex mutex;
	};
}