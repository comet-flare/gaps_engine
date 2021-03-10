#include <gapspch.hpp>
#include <Core/Input/Keyboard/KeyboardEvent.hpp>
#include <Core/Debugger/Debug.hpp>

MOD("Core.Input.Keyboard.Event");

namespace gaps
{
    KeyboardEvent::KeyboardEvent(const EventId id) noexcept
        :
        InputEvent{ id }
    {
        switch (id)
        {
        case gaps::EventId::KeyPress:
        case gaps::EventId::KeyRelease:
            break;
        default:
            this->id = EventId::Undefined;
            DEBUG_WARN("EventId is not from KeyboardEvent family. It will be set to Undefined!");
            break;
        }
    }
}