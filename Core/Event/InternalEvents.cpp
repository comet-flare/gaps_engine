#include <gapspch.hpp>
#include <Core/Event/InternalEvents.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Engine/Engine.hpp>

namespace gaps
{
	void InternalEvents::Register(GLFWwindow* pInternalWindow)
	{
		glfwSetFramebufferSizeCallback(pInternalWindow, FrameBufferSizeCallback);
	}

	void InternalEvents::FrameBufferSizeCallback(GLFWwindow* pWindowHandle, int32_t width, int32_t height)
	{
		Engine::pInstance->pWindow->HandleResize(width, height);
	}
}