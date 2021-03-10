#pragma once

#include "Event.hpp"

#define BIND_EVENT(DELEGATE) std::bind(&DELEGATE, this, std::placeholders::_1)

namespace gaps
{
	class EventDispatcher;
	class TickEvent;
	class KeyboardEvent;
	class MouseEvent;
	class WindowEvent;

	class IEventHandler
	{
	public:
		virtual ~IEventHandler() = default;

	protected:
		virtual void OnStartListening() = 0;
		virtual void OnStopListening() = 0;
		virtual bool OnEventDispatch(Event* pEvent) = 0;
	};

	class EventHandler : public IEventHandler
	{
	public:
		explicit EventHandler(int32_t priority = 0) noexcept;
		~EventHandler() override;

		virtual void StartListening() final;
		virtual void StopListening() final;

	protected:
		void OnStartListening() override;
		void OnStopListening() override;
		bool OnEventDispatch(Event* pEvent) override;

		std::function<bool(TickEvent)> TickHandler = nullptr;
		std::function<bool(KeyboardEvent)> KeyboardHandler = nullptr;
		std::function<bool(MouseEvent)> MouseHandler = nullptr;
		std::function<bool(WindowEvent)> WindowHandler = nullptr;

	private:
		int32_t priority;
		EventDispatcher* pEventDispatcher = nullptr;

		friend EventDispatcher;
	};
}