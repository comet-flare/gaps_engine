#include <gapspch.hpp>
#include <Core/Event/EventHandler.hpp>
#include <Core/Event/EventDispatcher.hpp>
#include <Core/Time/TickEvent.hpp>
#include <Core/Input/Keyboard/KeyboardEvent.hpp>
#include <Core/Input/Mouse/MouseEvent.hpp>
#include <Core/Window/WindowEvent.hpp>
#include <Core/Engine/Engine.hpp>

namespace gaps
{
	EventHandler::EventHandler(const int32_t priority) noexcept
		:
		priority{ priority },
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
		case EventId::KeyPress:
		case EventId::KeyRelease:
		{
			if (KeyboardHandler != nullptr)
			{
				bRes = KeyboardHandler(*dynamic_cast<KeyboardEvent*>(pEvent));
			}
			break;
		}
		case EventId::MouseButtonPress:
		case EventId::MouseButtonRelease:
		case EventId::MouseMotion:
		case EventId::MouseScroll:
		{
			if (MouseHandler != nullptr)
			{
				bRes = MouseHandler(*dynamic_cast<MouseEvent*>(pEvent));
			}
			break;
		}
		case EventId::WindowSizeChange:
		{
			if (WindowHandler != nullptr)
			{
				bRes = WindowHandler(*dynamic_cast<WindowEvent*>(pEvent));
			}
			break;
		}
		case EventId::Tick:
		{
			if (TickHandler != nullptr)
			{
				bRes = TickHandler(*dynamic_cast<TickEvent*>(pEvent));
			}
			break;
		}
		}

		return bRes;
	}
}