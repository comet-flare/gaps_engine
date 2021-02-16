#pragma once

namespace gaps
{
	enum class EventId : id_t
	{
		Undefined,
		WindowSizeChange
	};

	class IEvent
	{
	protected:
		virtual void OnCreate() = 0;
		virtual void OnRelease() = 0;
	};

	class Event : public IEvent
	{
	public:
		virtual ~Event() = default;

		EventId GetId() const noexcept;

	protected:
		Event(EventId id) noexcept;

		void OnCreate() override;
		void OnRelease() override;

	private:
		EventId id = EventId::Undefined;
	};

	struct EventQueue final
	{
		using EventType = std::pair<std::promise<bool>, std::unique_ptr<Event>>;
		std::queue<EventType> queue;
		std::mutex mutex;
	};
}