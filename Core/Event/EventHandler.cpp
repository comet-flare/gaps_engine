#include <gapspch.hpp>
#include <Core/Event/EventHandler.hpp>
#include <Core/Event/EventDispatcher.hpp>
#include <Core/Window/WindowEvent.hpp>
#include <Core/Engine/Engine.hpp>

namespace gaps
{
	EventHandler::EventHandler(int32_t priority) noexcept
		:
		priority{ std::move(priority) },
		pEventDispatcher{ Engine::pEventDispatcher }
	{
	}

	EventHandler::~EventHandler()
	{
		if (pEventDispatcher != nullptr)
		{
			pEventDispatcher->RemoveEventHandler(*this);
		}
	}

	void EventHandler::StartListening()
	{
		pEventDispatcher->AddEventHandler(*this);
		OnStartListening();
	}

	void EventHandler::StopListening()
	{
		if (pEventDispatcher != nullptr)
		{
			pEventDispatcher->RemoveEventHandler(*this);
			pEventDispatcher = nullptr;
		}

		OnStopListening();
	}

	void EventHandler::OnStartListening()
	{
	}

	void EventHandler::OnStopListening()
	{
	}

	bool EventHandler::OnEventDispatch(Event* pEvent)
	{
		bool bRes = false;

		switch (pEvent->GetId())
		{
		case EventId::Undefined: break;
		case EventId::WindowSizeChange:
		{
			if (WindowHandler != nullptr)
			{
				bRes = WindowHandler(*static_cast<WindowEvent*>(pEvent));
			}
			break;
		}
		}

		return bRes;
	}
}