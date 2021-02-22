#include <gapspch.hpp>
#include <Core/Input/Mouse/Mouse.hpp>
#include <Core/Input/Mouse/MouseEvent.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/Event/EventDispatcher.hpp>
#include <Core/Input/Input.hpp>

namespace gaps
{
    float Mouse::GetXPosition() const noexcept
    {
        return xPosition;
    }

    float Mouse::GetYPosition() const noexcept
    {
        return yPosition;
    }

    bool Mouse::IsButtonDown(MouseButton button) const
    {
        return bButtonStates[static_cast<uint32_t>(button)];
    }

    bool Mouse::HandleButtonPress(MouseButton button, float xPosition, float yPosition)
    {
        auto pEvent = std::make_unique<MouseEvent>(EventId::MouseButtonPress);
        pEvent->args.button = button;
        pEvent->args.xPosition = xPosition;
        pEvent->args.yPosition = yPosition;

        bButtonStates[static_cast<uint32_t>(button)] = true;

        return Engine::pEventDispatcher->DispatchEvent(std::move(pEvent));
    }

    bool Mouse::HandleButtonRelease(MouseButton button, float xPosition, float yPosition)
    {
        auto pEvent = std::make_unique<MouseEvent>(EventId::MouseButtonRelease);
        pEvent->args.button = button;
        pEvent->args.xPosition = xPosition;
        pEvent->args.yPosition = yPosition;

        bButtonStates[static_cast<uint32_t>(button)] = false;

        return Engine::pEventDispatcher->DispatchEvent(std::move(pEvent));
    }

    bool Mouse::HandleMotion(float xPosition, float yPosition)
    {
        auto pEvent = std::make_unique<MouseEvent>(EventId::MouseMotion);
        pEvent->args.xDifference = xPosition - this->xPosition;
        pEvent->args.yDifference = yPosition - this->yPosition;
        pEvent->args.xPosition = xPosition;
        pEvent->args.yPosition = yPosition;

        this->xPosition = xPosition;
        this->yPosition = yPosition;

        return Engine::pEventDispatcher->DispatchEvent(std::move(pEvent));
    }

    bool Mouse::HandleRelativeMotion(float xPosition, float yPosition)
    {
        float xNewPos = this->xPosition + xPosition;
        float yNewPos = this->yPosition + yPosition;

        xNewPos = std::clamp(xNewPos, 0.f, 1.f);
        yNewPos = std::clamp(yNewPos, 0.f, 1.f);

        return HandleMotion(xNewPos, yNewPos);
    }

    bool Mouse::HandleScroll(float xScroll, float yScroll, float xPosition, float yPosition)
    {
        auto pEvent = std::make_unique<MouseEvent>(EventId::MouseScroll);
        pEvent->args.xScroll = xScroll;
        pEvent->args.yScroll = yScroll;
        pEvent->args.xPosition = xPosition;
        pEvent->args.yPosition = yPosition;

        return Engine::pEventDispatcher->DispatchEvent(std::move(pEvent));
    }
}