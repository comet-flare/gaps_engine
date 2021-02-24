#pragma once

#include "../Event/Event.hpp"

namespace gaps
{
    class TickEvent final : public Event
    {
    public:
        TickEvent() noexcept;
        TickEvent(EventId id) noexcept;

        struct Args final
        {
            float deltaTime = 0.f;
        } args;
    };
}