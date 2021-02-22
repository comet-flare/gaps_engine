#pragma once

namespace gaps
{
	class InternalEvents final
	{
	public:
		static void Register(GLFWwindow* pInternalWindow);

		static void FrameBufferSizeCallback(GLFWwindow* pInternalWindow, int32_t width, int32_t height);
		static void KeyCallback(GLFWwindow* pInternalWindow, int32_t key, int32_t scanCode, int32_t action, int32_t modifiers);
		static void MouseButtonCallback(GLFWwindow* pInternalWindow, int32_t button, int32_t action, int32_t modifiers);
		static void MouseMotionCallback(GLFWwindow* pInternalWindow, double xPosition, double yPosition);
		static void MouseScrollCallback(GLFWwindow* pInternalWindow, double xScroll, double yScroll);
	};
}