#include <gapspch.hpp>
#include <Core/System/Window.hpp>
#include <Core/Debugger/Debug.hpp>

MOD("Core.System.Window");

namespace gaps
{
	Window::Window(WindowDescriptor desc) noexcept
		:
		desc{ std::move(desc) }
	{
	}

	int32_t Window::Create()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		pInternal = glfwCreateWindow
		(
			desc.width,
			desc.height,
			desc.title.c_str(),
			nullptr,
			nullptr
		);

		if (pInternal == nullptr)
		{
			DEBUG_CRIT("Failed to open GLFW Window!");
			Destroy();
			return EXIT_FAILURE;
		}

		glfwMakeContextCurrent(pInternal);

		return EXIT_SUCCESS;
	}

	void Window::Update()
	{
	}

	void Window::Destroy()
	{
		glfwTerminate();
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(pInternal);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(pInternal);
		glfwPollEvents();
	}

	const WindowDescriptor& Window::GetDescriptor() const noexcept
	{
		return desc;
	}
}