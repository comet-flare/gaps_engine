#include <gapspch.hpp>
#include <Core/Input/Mouse/MouseEvent.hpp>
#include <Core/Debugger/Debug.hpp>

MOD("Core.Input.Mouse.Event");

namespace gaps
{
    MouseEvent::MouseEvent(const EventId id) noexcept
        :
        InputEvent{ id }
    {
        switch (id)
        {
        case gaps::EventId::MouseButtonPress:
        case gaps::EventId::MouseButtonRelease:
        case gaps::EventId::MouseScroll:
        case gaps::EventId::MouseMotion:
            break;
        default:
            this->id = EventId::Undefined;
            DEBUG_WARN("EventId is not from MouseEvent family. It will be set to Undefined!");
            break;
        }
    }
}