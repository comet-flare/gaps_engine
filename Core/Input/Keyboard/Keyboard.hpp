#pragma once

#include "KeyCode.hpp"

namespace gaps
{
	class Keyboard final
	{
	public:
		bool IsKeyDown(KeyCode key) const noexcept;
		std::string CharsDown();
		std::string KeyToString(KeyCode key);

	private:
		bool HandleKeyPress(KeyCode key, KeyModifiers modifiers);
		bool HandleKeyRelease(KeyCode key, KeyModifiers modifiers);

		bool bKeyStates[static_cast<uint32_t>(KeyCode::Count)]{ false };
		KeyModifiers modifiers = KeyModifiers::None;

		friend class Input;
		friend class InternalEvents;
	};
}