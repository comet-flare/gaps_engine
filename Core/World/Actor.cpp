#include <gapspch.hpp>
#include <Core/World/Actor.hpp>

namespace gaps
{
    Actor::Actor(const bool bEnable)
    {
        if (bEnable)
        {
            Enable();
        }
    }

    void Actor::Enable()
    {
        if (!bEnabled)
        {
            bEnabled = true;
            StartListening();
            OnEnable();
        }
    }

    void Actor::Disable()
    {
        if (bEnabled)
        {
            bEnabled = false;
            StopListening();
            OnDisable();
        }
    }

    bool Actor::IsEnabled() const
    {
        return bEnabled;
    }

    void Actor::OnEnable()
    {
    }

    void Actor::OnDisable()
    {
    }
}