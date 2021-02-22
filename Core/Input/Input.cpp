#include <gapspch.hpp>
#include <Core/Input/Input.hpp>
#include <Core/Input/Keyboard/Keyboard.hpp>
#include <Core/Input/Keyboard/KeyboardEvent.hpp>
#include <Core/Input/Mouse/Mouse.hpp>
#include <Core/Input/Mouse/MouseEvent.hpp>
#include <Core/Debugger/Debug.hpp>

MOD("Core.Input");

namespace gaps
{
    void Input::RegisterDevices()
    {
        pKeyboard = new Keyboard();
        pMouse = new Mouse();
    }

    void Input::ReleaseDevices()
    {
        SAFE_RELEASE(pMouse);
        SAFE_RELEASE(pKeyboard);
    }

    void Input::Update()
    {
        InputEventQueue::EventType event;

        while (true)
        {
            std::unique_lock<std::mutex> lock{ inputEventQueue.mutex };

            if (inputEventQueue.queue.empty())
            {
                break;
            }

            event = std::move(inputEventQueue.queue.front());
            inputEventQueue.queue.pop();
            lock.unlock();

            event.first.set_value(HandleEvent(std::move(event.second)));
        }
    }

    bool Input::HandleEvent(std::unique_ptr<InputEvent> e)
    {
        switch (e->GetId())
        {
        case EventId::KeyPress:
        {
            auto pKeyboardEvent = static_cast<KeyboardEvent*>(e.get());
            return pKeyboard->HandleKeyPress
            (
                pKeyboardEvent->args.key,
                pKeyboardEvent->args.modifiers
            );
        }
        case EventId::KeyRelease:
        {
            auto pKeyboardEvent = static_cast<KeyboardEvent*>(e.get());
            return pKeyboard->HandleKeyRelease
            (
                pKeyboardEvent->args.key,
                pKeyboardEvent->args.modifiers
            );
        }
        case EventId::MouseButtonPress:
        {
            auto pMouseEvent = static_cast<MouseEvent*>(e.get());
            return pMouse->HandleButtonPress
            (
                pMouseEvent->args.button,
                pMouseEvent->args.xPosition,
                pMouseEvent->args.yPosition
            );
        }
        case EventId::MouseButtonRelease:
        {
            auto pMouseEvent = static_cast<MouseEvent*>(e.get());
            return pMouse->HandleButtonRelease
            (
                pMouseEvent->args.button,
                pMouseEvent->args.xPosition,
                pMouseEvent->args.yPosition
            );
        }
        case EventId::MouseMotion:
        {
            auto pMouseEvent = static_cast<MouseEvent*>(e.get());
            return pMouseEvent->args.bRelativeMotion
                ? pMouse->HandleRelativeMotion
                (
                    pMouseEvent->args.xPosition,
                    pMouseEvent->args.yPosition
                )
                : pMouse->HandleMotion
                (
                    pMouseEvent->args.xPosition,
                    pMouseEvent->args.yPosition
                );
        }
        case EventId::MouseScroll:
        {
            auto pMouseEvent = static_cast<MouseEvent*>(e.get());
            return pMouse->HandleScroll
            (
                pMouseEvent->args.xScroll,
                pMouseEvent->args.yScroll,
                pMouseEvent->args.xPosition,
                pMouseEvent->args.yPosition
            );
        }
        default:
        {
            DEBUG_WARN("Unhandled Event!");
        }
        }

        return false;
    }
}