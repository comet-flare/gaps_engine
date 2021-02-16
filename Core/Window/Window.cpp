#include <gapspch.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Debugger/Debug.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/Event/EventDispatcher.hpp>

MOD("Core.Window");

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
		WindowEvent e;

		while (true)
		{
			std::unique_lock<std::mutex> lock{ windowEventQueue.mutex };

			if (windowEventQueue.queue.empty())
			{
				break;
			}

			e = std::move(windowEventQueue.queue.front());
			windowEventQueue.queue.pop();
			lock.unlock();
			HandleEvent(e);
		}
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

	void Window::SubscribeEvent(WindowEvent e)
	{
		std::lock_guard<std::mutex> lock{ windowEventQueue.mutex };
		windowEventQueue.queue.push(e);
	}

	void Window::HandleEvent(WindowEvent e)
	{
		switch (e.GetId())
		{
		case EventId::WindowSizeChange:
		{
			desc.width = e.args.width;
			desc.height = e.args.height;

			auto sizeChangeEvent = std::make_unique<WindowEvent>(EventId::WindowSizeChange);
			sizeChangeEvent->pWindow = this;
			sizeChangeEvent->args.width = e.args.width;
			sizeChangeEvent->args.height = e.args.height;

			Engine::pInstance->pEventDispatcher->DispatchEvent(std::move(sizeChangeEvent));
			break;
		}
		default:
		{
			DEBUG_WARN("Unhandled Event!");
		}
		}
	}

	void Window::HandleResize(int32_t width, int32_t height)
	{
		WindowEvent windowEvent{ EventId::WindowSizeChange };
		windowEvent.args.width = width;
		windowEvent.args.height = height;
		
		SubscribeEvent(windowEvent);
	}
}