#pragma once

#include "InputEvent.hpp"

namespace gaps
{
	class Keyboard;
	class Mouse;

	class Input final
	{
	public:
		inline static Keyboard* pKeyboard = nullptr;
		inline static Mouse* pMouse = nullptr;

	private:
		static void RegisterDevices();
		static void ReleaseDevices();
		static void Update();
		static bool HandleEvent(std::unique_ptr<InputEvent> e);

		inline static InputEventQueue inputEventQueue;

		friend class Engine;
	};
}