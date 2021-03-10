#pragma once

#include "Event.hpp"

namespace gaps
{
	class EventHandler;

	class EventDispatcher final
	{
	public:
		~EventDispatcher();

		void AddEventHandler(EventHandler& eventHandler);
		void RemoveEventHandler(EventHandler& eventHandler);

		bool DispatchEvent(std::unique_ptr<Event> pEvent);
		std::future<bool> PostEvent(std::unique_ptr<Event> pEvent);

		void DispatchEvents();

	private:
		std::vector<EventHandler*> eventHandlers;
		std::set<EventHandler*> eventHandlerAdd;
		std::set<EventHandler*> eventHandlerDel;
		EventQueue eventQueue;
	};
}