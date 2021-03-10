#pragma once

namespace gaps
{
	enum class EventId : id_t
	{
		Undefined,

		// Process Events
		Tick,

		// Keyboard Events
		KeyPress,
		KeyRelease,

		// Mouse Events
		MouseButtonPress,
		MouseButtonRelease,
		MouseMotion,
		MouseScroll,

		// Window Events
		WindowSizeChange
	};

	class IEvent
	{
	public:
		virtual ~IEvent() = default;

	protected:
		virtual void OnCreate() = 0;
		virtual void OnRelease() = 0;
	};

	class Event : public IEvent
	{
	public:
		EventId GetId() const noexcept;

	protected:
		explicit Event(EventId id) noexcept;

		void OnCreate() override;
		void OnRelease() override;

		EventId id = EventId::Undefined;
	};

	struct EventQueue final
	{
		using EventType = std::pair<std::promise<bool>, std::unique_ptr<Event>>;
		std::queue<EventType> queue;
		std::mutex mutex;
	};
}