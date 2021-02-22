#include <gapspch.hpp>
#include <Core/Input/Keyboard/Keyboard.hpp>
#include <Core/Input/Keyboard/KeyboardEvent.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/Event/EventDispatcher.hpp>

namespace gaps
{
	bool Keyboard::IsKeyDown(KeyCode key) const noexcept
	{
		return bKeyStates[static_cast<uint32_t>(key)];
	}

    std::string Keyboard::CharsDown()
    {
        std::string res = "";

        static KeyCode printableKeys[] =
        {
            KeyCode::Space,
            KeyCode::Apostrophe,
            KeyCode::Comma,
            KeyCode::Minus,
            KeyCode::Period,
            KeyCode::Slash,
            KeyCode::Key0,
            KeyCode::Key1,
            KeyCode::Key2,
            KeyCode::Key3,
            KeyCode::Key4,
            KeyCode::Key5,
            KeyCode::Key6,
            KeyCode::Key7,
            KeyCode::Key8,
            KeyCode::Key9,
            KeyCode::Semicolon,
            KeyCode::Equal,
            KeyCode::A,
            KeyCode::B,
            KeyCode::C,
            KeyCode::D,
            KeyCode::E,
            KeyCode::F,
            KeyCode::G,
            KeyCode::H,
            KeyCode::I,
            KeyCode::J,
            KeyCode::K,
            KeyCode::L,
            KeyCode::M,
            KeyCode::N,
            KeyCode::O,
            KeyCode::P,
            KeyCode::Q,
            KeyCode::R,
            KeyCode::S,
            KeyCode::T,
            KeyCode::U,
            KeyCode::V,
            KeyCode::W,
            KeyCode::X,
            KeyCode::Y,
            KeyCode::Z,
            KeyCode::LeftBracket,
            KeyCode::Backslash,
            KeyCode::RightBracket,
            KeyCode::GraveAccent
        };

        for (const auto& key : printableKeys)
        {
            if (IsKeyDown(key))
            {
                res += KeyToString(key);
            }
        }

        return res;
    }

    std::string Keyboard::KeyToString(KeyCode key)
    {
        bool bCapsLock = static_cast<bool>(modifiers & KeyModifiers::CapsLock);
        bool bShift = static_cast<bool>(modifiers & KeyModifiers::Shift);

        switch (key)
        {
        case KeyCode::Space: return " ";
        case KeyCode::Apostrophe: return bShift ? "\"" : "'";
        case KeyCode::Comma: return bShift ? "<" : ",";
        case KeyCode::Minus: return bShift ? "_" : "-";
        case KeyCode::Period: return bShift ? ">" : ".";
        case KeyCode::Slash: return bShift ? "?" : "/";
        case KeyCode::Key0: return bShift ? "!" : "0";
        case KeyCode::Key1: return bShift ? "@" : "1";
        case KeyCode::Key2: return bShift ? "#" : "2";
        case KeyCode::Key3: return bShift ? "$" : "3";
        case KeyCode::Key4: return bShift ? "%" : "4";
        case KeyCode::Key5: return bShift ? "^" : "5";
        case KeyCode::Key6: return bShift ? "&" : "6";
        case KeyCode::Key7: return bShift ? "*" : "7";
        case KeyCode::Key8: return bShift ? "(" : "8";
        case KeyCode::Key9: return bShift ? ")" : "9";
        case KeyCode::Semicolon: return bShift ? ":" : ";";
        case KeyCode::Equal: return bShift ? "+" : "=";
        case KeyCode::A: return bCapsLock ? (bShift ? "a" : "A") : (bShift ? "A" : "a");
        case KeyCode::B: return bCapsLock ? (bShift ? "b" : "B") : (bShift ? "B" : "b");
        case KeyCode::C: return bCapsLock ? (bShift ? "c" : "C") : (bShift ? "C" : "c");
        case KeyCode::D: return bCapsLock ? (bShift ? "d" : "D") : (bShift ? "D" : "d");
        case KeyCode::E: return bCapsLock ? (bShift ? "e" : "E") : (bShift ? "E" : "e");
        case KeyCode::F: return bCapsLock ? (bShift ? "f" : "F") : (bShift ? "F" : "f");
        case KeyCode::G: return bCapsLock ? (bShift ? "g" : "G") : (bShift ? "G" : "g");
        case KeyCode::H: return bCapsLock ? (bShift ? "h" : "H") : (bShift ? "H" : "h");
        case KeyCode::I: return bCapsLock ? (bShift ? "i" : "I") : (bShift ? "I" : "i");
        case KeyCode::J: return bCapsLock ? (bShift ? "j" : "J") : (bShift ? "J" : "j");
        case KeyCode::K: return bCapsLock ? (bShift ? "k" : "K") : (bShift ? "K" : "k");
        case KeyCode::L: return bCapsLock ? (bShift ? "l" : "L") : (bShift ? "L" : "l");
        case KeyCode::M: return bCapsLock ? (bShift ? "m" : "M") : (bShift ? "M" : "m");
        case KeyCode::N: return bCapsLock ? (bShift ? "n" : "N") : (bShift ? "N" : "n");
        case KeyCode::O: return bCapsLock ? (bShift ? "o" : "O") : (bShift ? "O" : "o");
        case KeyCode::P: return bCapsLock ? (bShift ? "p" : "P") : (bShift ? "P" : "p");
        case KeyCode::Q: return bCapsLock ? (bShift ? "q" : "Q") : (bShift ? "Q" : "q");
        case KeyCode::R: return bCapsLock ? (bShift ? "r" : "R") : (bShift ? "R" : "r");
        case KeyCode::S: return bCapsLock ? (bShift ? "s" : "S") : (bShift ? "S" : "s");
        case KeyCode::T: return bCapsLock ? (bShift ? "t" : "T") : (bShift ? "T" : "t");
        case KeyCode::U: return bCapsLock ? (bShift ? "u" : "U") : (bShift ? "U" : "u");
        case KeyCode::V: return bCapsLock ? (bShift ? "v" : "V") : (bShift ? "V" : "v");
        case KeyCode::W: return bCapsLock ? (bShift ? "w" : "W") : (bShift ? "W" : "w");
        case KeyCode::X: return bCapsLock ? (bShift ? "x" : "X") : (bShift ? "X" : "x");
        case KeyCode::Y: return bCapsLock ? (bShift ? "y" : "Y") : (bShift ? "Y" : "y");
        case KeyCode::Z: return bCapsLock ? (bShift ? "z" : "Z") : (bShift ? "Z" : "z");
        case KeyCode::LeftBracket: return bShift ? "{" : "[";
        case KeyCode::Backslash: return bShift ? "|" : "\\";
        case KeyCode::RightBracket: return bShift ? "}" : "]";
        case KeyCode::GraveAccent: return bShift ? "~" : "`";
        default: return "";
        }
    }

    bool Keyboard::HandleKeyPress(KeyCode key, KeyModifiers modifiers)
    {
        if (bKeyStates[static_cast<uint32_t>(key)])
        {
            return false;
        }

        auto pEvent = std::make_unique<KeyboardEvent>(EventId::KeyPress);
        pEvent->args.key = key;
        pEvent->args.modifiers = modifiers;

        bKeyStates[static_cast<uint32_t>(key)] = true;
        this->modifiers = modifiers;

        return Engine::pEventDispatcher->DispatchEvent(std::move(pEvent));
    }

    bool Keyboard::HandleKeyRelease(KeyCode key, KeyModifiers modifiers)
    {
        auto pEvent = std::make_unique<KeyboardEvent>(EventId::KeyRelease);
        pEvent->args.key = key;
        pEvent->args.modifiers = modifiers;

        bKeyStates[static_cast<uint32_t>(key)] = false;
        this->modifiers = modifiers;

        return Engine::pEventDispatcher->DispatchEvent(std::move(pEvent));
    }
}