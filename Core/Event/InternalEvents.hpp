#pragma once

namespace gaps
{
	class InternalEvents final
	{
	public:
		static void Register(GLFWwindow* pInternalWindow);
		static void FrameBufferSizeCallback(GLFWwindow* pWindowHandle, int32_t width, int32_t height);
	};
}