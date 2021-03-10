#include <gapspch.hpp>
#include <Core/Event/InternalEvents.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/Input/Input.hpp>
#include <Core/Input/Keyboard/Keyboard.hpp>
#include <Core/Input/Mouse/Mouse.hpp>

namespace gaps
{
	void InternalEvents::Register(GLFWwindow* pInternalWindow)
	{
		glfwSetFramebufferSizeCallback(pInternalWindow, FrameBufferSizeCallback);

		glfwSetInputMode(pInternalWindow, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
		glfwSetKeyCallback(pInternalWindow, KeyCallback);
		glfwSetMouseButtonCallback(pInternalWindow, MouseButtonCallback);
		glfwSetCursorPosCallback(pInternalWindow, MouseMotionCallback);
		glfwSetScrollCallback(pInternalWindow, MouseScrollCallback);
	}

	void InternalEvents::FrameBufferSizeCallback(GLFWwindow* pWindowHandle, int32_t width, int32_t height)
	{
		Engine::pWindow->HandleResize(width, height);
	}

	void InternalEvents::KeyCallback(GLFWwindow* pInternalWindow, int32_t key, int32_t scanCode, int32_t action, int32_t modifiers)
	{
		switch (action)
		{
		case GLFW_PRESS:
			Input::pKeyboard->HandleKeyPress
			(
				static_cast<KeyCode>(key),
				static_cast<KeyModifiers>(modifiers)
			);
			break;
		case GLFW_RELEASE:
			Input::pKeyboard->HandleKeyRelease
			(
				static_cast<KeyCode>(key),
				static_cast<KeyModifiers>(modifiers)
			);
			break;
		default: break;
		}
	}

	void InternalEvents::MouseButtonCallback(GLFWwindow* pInternalWindow, int32_t button, int32_t action, int32_t modifiers)
	{
		double xPosition = 0.0;
		double yPosition = 0.0;
		glfwGetCursorPos(pInternalWindow, &xPosition, &yPosition);

		auto mouseButton = static_cast<MouseButton>(button + 1);
		if (mouseButton == MouseButton::Right && modifiers & GLFW_MOD_ALT)
		{
			mouseButton = MouseButton::Middle;
		}

		switch (action)
		{
		case GLFW_PRESS:
			Input::pMouse->HandleButtonPress
			(
				static_cast<MouseButton>(mouseButton),
				static_cast<float>(xPosition),
				static_cast<float>(yPosition)
			);
			break;
		case GLFW_RELEASE:
			Input::pMouse->HandleButtonRelease
			(
				static_cast<MouseButton>(mouseButton),
				static_cast<float>(xPosition),
				static_cast<float>(yPosition)
			);
			break;
		default: break;
		}
	}

	void InternalEvents::MouseMotionCallback(GLFWwindow* pInternalWindow, double xPosition, double yPosition)
	{
		Input::pMouse->HandleMotion
		(
			static_cast<float>(xPosition),
			static_cast<float>(yPosition)
		);
	}

	void InternalEvents::MouseScrollCallback(GLFWwindow* pInternalWindow, double xScroll, double yScroll)
	{
		double xPosition = 0.0;
		double yPosition = 0.0;
		glfwGetCursorPos(pInternalWindow, &xPosition, &yPosition);

		Input::pMouse->HandleScroll
		(
			static_cast<float>(xScroll),
			static_cast<float>(yScroll),
			static_cast<float>(xPosition),
			static_cast<float>(yPosition)
		);
	}
}