#pragma once

#include "WindowEvent.hpp"

namespace gaps
{
	struct WindowDescriptor final
	{
		uint32_t width = 1920u;
		uint32_t height = 1080u;
		std::string title = "GAPS Engine";
	};

	class Window final
	{
	public:
		explicit Window(WindowDescriptor desc = {}) noexcept;

		int32_t Create();
		void Update();
		void Destroy();

		bool ShouldClose();
		void SwapBuffers();

		const WindowDescriptor& GetDescriptor() const noexcept;

	private:
		void SubscribeEvent(WindowEvent e);
		void HandleEvent(WindowEvent e);
		void HandleResize(int32_t width, int32_t height);

		WindowDescriptor desc;
		GLFWwindow* pInternal = nullptr;
		WindowEventQueue windowEventQueue;

		friend class Engine;
		friend class InternalEvents;
	};
}