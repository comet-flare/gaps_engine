#include <gapspch.hpp>
#include <Core/Event/EventDispatcher.hpp>
#include <Core/Event/EventHandler.hpp>

namespace gaps
{
	EventDispatcher::~EventDispatcher()
	{
		for (const auto& pEventHandler : eventHandlerAdd)
		{
			pEventHandler->pEventDispatcher = nullptr;
		}

		for (const auto& pEventHandler : eventHandlers)
		{
			const auto& it = std::find
			(
				eventHandlerDel.begin(),
				eventHandlerDel.end(),
				pEventHandler
			);

			if (it == eventHandlerDel.end())
			{
				pEventHandler->pEventDispatcher = nullptr;
			}
		}
	}

	void EventDispatcher::AddEventHandler(EventHandler& eventHandler)
	{
		if (eventHandler.pEventDispatcher != nullptr)
		{
			eventHandler.pEventDispatcher->RemoveEventHandler(eventHandler);
		}

		eventHandler.pEventDispatcher = this;
		eventHandlerAdd.insert(&eventHandler);

		const auto& it = eventHandlerDel.find(&eventHandler);
		if (it != eventHandlerDel.end())
		{
			eventHandlerDel.erase(it);
		}
	}

	void EventDispatcher::RemoveEventHandler(EventHandler& eventHandler)
	{
		if (eventHandler.pEventDispatcher == this)
		{
			eventHandler.pEventDispatcher = nullptr;
		}

		eventHandlerDel.insert(&eventHandler);

		const auto& it = eventHandlerAdd.find(&eventHandler);
		if (it != eventHandlerAdd.end())
		{
			eventHandlerAdd.erase(it);
		}
	}

	bool EventDispatcher::DispatchEvent(std::unique_ptr<Event> pEvent)
	{
		if (pEvent == nullptr)
		{
			return false;
		}

		bool bHandled = false;

		for (const auto& pEventHandler : eventHandlers)
		{
			const auto& it = std::find
			(
				eventHandlerDel.begin(),
				eventHandlerDel.end(),
				pEventHandler
			);

			if (it == eventHandlerDel.end())
			{
				bHandled = pEventHandler->OnEventDispatch(pEvent.get());
			}

			if (bHandled)
			{
				break;
			}
		}

		return bHandled;
	}

	std::future<bool> EventDispatcher::PostEvent(std::unique_ptr<Event> pEvent)
	{
		std::promise<bool> promise;
		std::future<bool> future = promise.get_future();
		std::lock_guard lock{ eventQueue.mutex };
		eventQueue.queue.push({ std::move(promise), std::move(pEvent) });
		return future;
	}

	void EventDispatcher::DispatchEvents()
	{
		for (const auto& pEventHandler : eventHandlerDel)
		{
			const auto& it = std::find
			(
				eventHandlers.begin(),
				eventHandlers.end(),
				pEventHandler
			);

			if (it != eventHandlers.end())
			{
				eventHandlers.erase(it);
			}
		}

		eventHandlerDel.clear();

		for (const auto& pEventHandler : eventHandlerAdd)
		{
			const auto& it = std::find
			(
				eventHandlers.begin(),
				eventHandlers.end(),
				pEventHandler
			);

			if (it == eventHandlers.end())
			{
				auto upperBound = std::upper_bound
				(
					eventHandlers.begin(),
					eventHandlers.end(),
					pEventHandler,
					[](const auto& pFirst, const auto& pSecond) noexcept
					{
						return pFirst->priority > pSecond->priority;
					}
				);

				eventHandlers.insert(upperBound, pEventHandler);
			}
		}

		eventHandlerAdd.clear();

		EventQueue::EventType event;

		while (true)
		{
			std::unique_lock<std::mutex> lock{ eventQueue.mutex };

			if (eventQueue.queue.empty())
			{
				break;
			}

			event = std::move(eventQueue.queue.front());
			eventQueue.queue.pop();
			lock.unlock();

			event.first.set_value(DispatchEvent(std::move(event.second)));
		}
	}
}